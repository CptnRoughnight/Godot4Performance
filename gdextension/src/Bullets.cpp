#include "Bullets.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;


void Bullets::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("getTexture"),&Bullets::getTexture);
    ClassDB::bind_method(D_METHOD("setTexture","sprite"),&Bullets::setTexture);
    ClassDB::add_property("Bullets",PropertyInfo(Variant::OBJECT,"sprite",PROPERTY_HINT_RESOURCE_TYPE,"Texture2D"),"setTexture","getTexture");

    ClassDB::bind_method(D_METHOD("getNumSprites"),&Bullets::getNumSprites);
    ClassDB::bind_method(D_METHOD("setNumSprites","numSprites"),&Bullets::setNumSprites);
    ClassDB::add_property("Bullets",PropertyInfo(Variant::INT,"numSprites"),"setNumSprites","getNumSprites");
}


Bullets::Bullets()
{
    numSprites = 100;
    if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
}


Bullets::~Bullets()
{
}

void Bullets::_exit_tree()
{
    /*memdelete (rng);
    for (int i=0;i<numSprites;i++)
        memdelete (sprites[i]);*/
}

void Bullets::_ready()
{
   if (!Engine::get_singleton()->is_editor_hint())
   {
        UtilityFunctions::print("Generating Sprites");
        rng = memnew (RandomNumberGenerator);
        
        speed = 200.0f;
        positions = new Vector2[numSprites];
        directions = new Vector2[numSprites];
        sprites = new Sprite2D*[numSprites];        

        for (int i=0;i<numSprites;i++)
        {
            sprites[i] = memnew (Sprite2D);
            positions[i].x = rng->randf()*1920;
            positions[i].y = rng->randf()*1080;
            directions[i].x = rng->randf_range(-speed,speed); 
            directions[i].y = rng->randf_range(-speed,speed);
            add_child(sprites[i]);
            sprites[i]->set_position(positions[i]);
            sprites[i]->set_texture(getTexture());
        }
   }
}


void Bullets::_physics_process(double delta)
{
    for (int i=0;i<numSprites;i++)
    {
        positions[i].x += directions[i].x * (float)delta;
        positions[i].y += directions[i].y * (float)delta;
        if ((positions[i].x < 0) || (positions[i].x > 1920))
            directions[i] *= -1;
        if ((positions[i].y < 0) || (positions[i].y > 1080))
            directions[i] *= -1;
        sprites[i]->set_position(positions[i]);
    }
}


void Bullets::setTexture(const Ref<Texture2D> _sprite)
{
    sprite = _sprite;
}


Ref<Texture2D> Bullets::getTexture()
{
    return sprite;
}

void Bullets::setNumSprites(const int _numSprites)
{
    numSprites = _numSprites;
}


int Bullets::getNumSprites()
{
    return numSprites;
}