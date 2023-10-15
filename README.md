# Godot4Performance
 Testing Perfomance of Godot4
 Here are some examples to demonstrate perfomance of Godot4
 I'm using Godot4.2.beta1.mono.official
 
# Testing Scenario
First Test is a 2D Multimesh Test both written in GDScript and C#.
Results: Spawning&moving Sprites before the fps drops under 60fps.

41000 bullets with GDScript (MultimeshInstance2D)
125000 bullets with C# (MultiMeshInstance2D)
100000 bullets with GDExtension (instanced Sprite2D)
160000 bullets with GDExtension (MultiMeshInstance2D)

(My testing machine : Ryzen 7 5800X,32gRam,Radeon 6600XT)

# Improvements
If anyone has tips and tricks to increase performance even further, please let me know :)

