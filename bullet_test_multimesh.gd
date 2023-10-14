extends Node2D

const SPEED := 200.0

@onready var multimesh : MultiMeshInstance2D = $MultiMeshInstance2D
@onready var fps : Label = $Debug/HBoxContainer/FPS
@onready var bullets : Label = $Debug/HBoxContainer/Bullets

var mesh  = preload("res://bullet_mesh.tres")

var multi : MultiMesh
var positions : Array[Vector2] = []
var directions: Array[Vector2] = []
var v : Vector2
var d : Vector2
var t : Transform2D
var count : int = 0

func _ready() -> void:
	multimesh.multimesh.mesh = mesh
	multi = multimesh.multimesh
	for i in multi.instance_count:
		v = Vector2(randi_range(0,1920),randi_range(0,1080))
		t = Transform2D(0.0,v)
		positions.append(v)
		directions.append(Vector2(randf_range(-SPEED,SPEED),randf_range(-SPEED,SPEED)))
		multi.set_instance_transform_2d(i, t)
	count = multi.instance_count

func _physics_process(delta: float) -> void:
	fps.text = "FPS " + str(Engine.get_frames_per_second())
	bullets.text = "Bullets : " + str(multimesh.multimesh.instance_count)
	
	if (Input.is_action_pressed("shoot")):
		multimesh.visible = false
		multi.instance_count += 10
		count = multi.instance_count
		return 
		
	if Input.is_action_just_released("shoot"):
		positions.clear()
		directions.clear()
		for i in count:
			var v = Vector2(randi_range(0,1920),randi_range(0,1080))
			var t = Transform2D(0.0,v)
			positions.append(v)
			directions.append(Vector2(randf_range(-SPEED,SPEED),randf_range(-SPEED,SPEED)))
			multi.set_instance_transform_2d(i, t)
		multimesh.visible = true	
			
	if Input.is_action_just_pressed("exit"):
		get_tree().quit()
		
	animate(delta)

func animate(delta) -> void:
	for i in count:
		v = positions[i]
		d = directions[i]
		v.x += d.x * delta
		v.y += d.y * delta
		if (v.x < 0) or (v.x > 1920):
			directions[i].x *= -1
		if (v.y < 0) or (v.y > 1080):
			directions[i].y *= -1
		t.origin = v
		positions[i] = v
		
		multi.set_instance_transform_2d(i, t)
