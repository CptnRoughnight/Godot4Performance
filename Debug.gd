extends CanvasLayer

@onready var fps = $HBoxContainer/FPS

func _physics_process(_delta: float) -> void:
	fps.text = "FPS : " + str(Engine.get_frames_per_second())
