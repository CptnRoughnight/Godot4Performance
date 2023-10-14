using Godot;
using System;
using System.Collections.Generic;

public partial class bullet_test_multimesh_sharp : Node2D
{
	private const float SPEED = 200.0f;

	private Label fps;
	private Label bullets;
	private MultiMeshInstance2D multiMesh;
	private MultiMesh multi;
	private ArrayMesh bulletMesh;


	private Vector2 v = new Vector2();
	private Vector2 d = new Vector2();
	private Transform2D t;

	private Vector2[] positions;
	private Vector2[] directions;
	private int count;

	private RandomNumberGenerator rng = new RandomNumberGenerator();

	public override void _Ready()
	{
		fps = GetNode<Label>("Debug/HBoxContainer/FPS");
		bullets = GetNode<Label>("Debug/HBoxContainer/Bullets");
		multiMesh = GetNode<MultiMeshInstance2D>("MultiMeshInstance2D");
		multi = multiMesh.Multimesh;
		bulletMesh = ResourceLoader.Load<ArrayMesh>("res://bullet_mesh.tres");
		positions = new Vector2[multi.InstanceCount];
		directions = new Vector2[multi.InstanceCount];
		count = multi.InstanceCount;
		for (int i=0;i<count;i++)
		{
			v = new Vector2(rng.RandiRange(0,1920),rng.RandiRange(0,1080));
			t = new Transform2D(0.0f,v);
			positions[i] = v;
			directions[i] = new Vector2(rng.RandfRange(-SPEED,SPEED),rng.RandfRange(-SPEED,SPEED));
			multi.SetInstanceTransform2D(i,t);
		}
	}

    public override void _PhysicsProcess(double delta)
    {
		fps.Text = "FPS :" + Engine.GetFramesPerSecond().ToString();
		bullets.Text = "Bullets : " + multi.InstanceCount.ToString();

		Animate((float)delta);
    }

	private void Animate(float delta)
	{
		for (int i=0;i<count;i++)
		{
			v = positions[i];
			d = directions[i];
			v.X += d.X * delta;
			v.Y += d.Y * delta;
			float x = directions[i].X;
			float y = directions[i].Y;
			if ((v.X < 0) || (v.X > 1920))
				x *= -1;
			if ((v.Y < 0) || (v.Y > 1920))
				y *= -1;
			directions[i].X = x;
			directions[i].Y = y;

			t.Origin = v;
			positions[i] = v;
			multi.SetInstanceTransform2D(i,t);
		}
	}
}
