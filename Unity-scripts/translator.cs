using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class rotator : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		transform.translate (new Vector3 (0.0f, -0.1f, 0.0f) * Time.deltaTime);


	}
}
