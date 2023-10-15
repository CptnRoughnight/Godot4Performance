#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/multi_mesh_instance2d.hpp>
#include <godot_cpp/classes/multi_mesh.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/array_mesh.hpp>


namespace godot
{
    class BulletMulti : public Node2D
    {
        GDCLASS(BulletMulti,Node2D);

        private:
            Vector2* positions;
            Vector2* directions;
            Transform2D** transforms;
            float speed;
            Ref<Texture2D> sprite;
            int numSprites;
            RandomNumberGenerator* rng;
            MultiMeshInstance2D* multimesh;
            MultiMesh* multi;
            Ref<ArrayMesh> mesh;


        protected:
            static void _bind_methods();

        public:
            BulletMulti();
            ~BulletMulti();

            void _ready();
            void _physics_process(double delat);
            void _exit_tree();
            

            void setTexture(const Ref<Texture2D> _sprite);
            Ref<Texture2D> getTexture();
            void setNumSprites(const int _numSprites);
            int getNumSprites();
            void setMesh(const Ref<ArrayMesh> _mesh);
            Ref<ArrayMesh> getMesh();
    };
}