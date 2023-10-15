#include "BulletMulti.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;


void BulletMulti::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("getTexture"),&BulletMulti::getTexture);
    ClassDB::bind_method(D_METHOD("setTexture","sprite"),&BulletMulti::setTexture);
    ClassDB::add_property("BulletMulti",PropertyInfo(Variant::OBJECT,"sprite",PROPERTY_HINT_RESOURCE_TYPE,"Texture2D"),"setTexture","getTexture");

    ClassDB::bind_method(D_METHOD("getNumSprites"),&BulletMulti::getNumSprites);
    ClassDB::bind_method(D_METHOD("setNumSprites","numSprites"),&BulletMulti::setNumSprites);
    ClassDB::add_property("BulletMulti",PropertyInfo(Variant::INT,"numSprites"),"setNumSprites","getNumSprites");

    ClassDB::bind_method(D_METHOD("getMesh"),&BulletMulti::getMesh);
    ClassDB::bind_method(D_METHOD("setMesh","mesh"),&BulletMulti::setMesh);
    ClassDB::add_property("BulletMulti",PropertyInfo(Variant::OBJECT,"mesh",PROPERTY_HINT_RESOURCE_TYPE,"ArrayMesh"),"setMesh","getMesh");
}


BulletMulti::BulletMulti()
{
    numSprites = 100;
    if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
}


BulletMulti::~BulletMulti()
{
}

void BulletMulti::_exit_tree()
{
 /*   memdelete (rng);
    memdelete (multi);
    memdelete (multimesh);*/
}

void BulletMulti::_ready()
{
   if (!Engine::get_singleton()->is_editor_hint())
   {
        UtilityFunctions::print("Generating Multimesh");
        rng = memnew (RandomNumberGenerator);
        
        speed = 200.0f;
        positions = new Vector2[numSprites];
        directions = new Vector2[numSprites];
        transforms = new Transform2D*[numSprites];

        multimesh = memnew (MultiMeshInstance2D);
        add_child(multimesh);
        multi = memnew (MultiMesh);
        multi->set_mesh(mesh);
        multi->set_instance_count(numSprites);
        multimesh->set_multimesh(multi);
        multimesh->set_texture(sprite);

        for (int i=0;i<numSprites;i++)
        {
            positions[i].x = rng->randf()*1920;
            positions[i].y = rng->randf()*1080;
            directions[i].x = rng->randf_range(-speed,speed); 
            directions[i].y = rng->randf_range(-speed,speed);
            transforms[i] = new Transform2D(0.0f,positions[i]);
            multi->set_instance_transform_2d(i,*transforms[i]);
            
        }
   }
}


void BulletMulti::_physics_process(double delta)
{
    for (int i=0;i<numSprites;i++)
    {
        positions[i].x += directions[i].x * (float)delta;
        positions[i].y += directions[i].y * (float)delta;
        if ((positions[i].x < 0) || (positions[i].x > 1920))
            directions[i] *= -1;
        if ((positions[i].y < 0) || (positions[i].y > 1080))
            directions[i] *= -1;
        transforms[i]->set_origin(positions[i]);
        multi->set_instance_transform_2d(i,*transforms[i]);
    }
}


void BulletMulti::setTexture(const Ref<Texture2D> _sprite)
{
    sprite = _sprite;
}


Ref<Texture2D> BulletMulti::getTexture()
{
    return sprite;
}

void BulletMulti::setNumSprites(const int _numSprites)
{
    numSprites = _numSprites;
}


int BulletMulti::getNumSprites()
{
    return numSprites;
}

void BulletMulti::setMesh(const Ref<ArrayMesh> _mesh)
{
    mesh = _mesh;
}


Ref<ArrayMesh> BulletMulti::getMesh()
{
    return mesh;
}