#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/multi_mesh_instance2d.hpp>
#include <godot_cpp/classes/multi_mesh.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

namespace godot
{
    class Bullets : public Node2D
    {
        GDCLASS(Bullets,Node2D);

        private:
            Vector2* positions;
            Vector2* directions;
            float speed;
            Sprite2D** sprites;
            Ref<Texture2D> sprite;
            int numSprites;
            RandomNumberGenerator* rng;

        protected:
            static void _bind_methods();

        public:
            Bullets();
            ~Bullets();

            void _ready();
            void _physics_process(double delat);
            void _exit_tree();
            

            void setTexture(const Ref<Texture2D> _sprite);
            Ref<Texture2D> getTexture();
            void setNumSprites(const int _numSprites);
            int getNumSprites();
    };
}