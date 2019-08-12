using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraControl : MonoBehaviour {

	public GameObject player;


	private Vector3 offset;
	float smooth = 5.0f;
	float tiltAngle = 0.0f;
	float panAngle = 0.0f;
	float sensitivity = 1.0f;


	void Start ()
	{
		offset = transform.position - player.transform.position;
	}

	void Update(){


		if (Input.GetKeyDown (KeyCode.Z)) {
			tiltAngle -= sensitivity;
		} 
		else if (Input.GetKeyDown (KeyCode.X)) {
			tiltAngle += sensitivity;
		} 
		else if (Input.GetKeyDown (KeyCode.C)) {
			panAngle += sensitivity;
		} 
		else if (Input.GetKeyDown (KeyCode.V)) {
			panAngle -= sensitivity;
		} 


		// Smoothly tilts a transform towards a target rotation.
		float tiltAroundY = tiltAngle;
		float tiltAroundX = panAngle;

		Quaternion target = Quaternion.Euler(tiltAroundX, tiltAroundY,0);

		// Dampen towards the target rotation
		transform.rotation = Quaternion.Slerp(transform.rotation, target,  Time.deltaTime * smooth);

	}

	void LateUpdate ()
	{

		transform.position = player.transform.position + offset;
	}
}


