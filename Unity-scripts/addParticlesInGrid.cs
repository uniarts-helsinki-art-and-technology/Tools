using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class addParticlesInGrid : MonoBehaviour {

	private ParticleGrid[] particles;
	private int num;

	// Use this for initialization
	void Start () {
		num = 100;
		particles = new ParticleGrid[num];
		for (int i = 0; i < 10; ++i){
			for (int j = 0; j < 10; ++j){

				particles[i+j] = new ParticleGrid ();
				particles[i+j].setStartPosition(i,j);
		}
	}
	}
	
	// Update is called once per frame
	void Update () {

		for (int i = 0; i < 10; ++i){
			for (int j = 0; j < 10; ++j){
			if (particles[i+j].isDead ()) {
					particles[i+j].killParticle ();
					particles[i+j] = new ParticleGrid ();
					particles[i+j].setStartPosition(i,j);
			} else {
					particles[i+j].updatePosition ();
			}
		}
	}
}
}

public class ParticleGrid : MonoBehaviour {

	private Vector3 myPosition;
	private Vector3 myVelocity;
	private float life;
	GameObject b;
	Rigidbody rb;

			
	public ParticleGrid(){
		b = GameObject.CreatePrimitive (PrimitiveType.Sphere);
		rb = b.AddComponent<Rigidbody>();
		rb.isKinematic=false;
		life = Random.Range (100, 1000);
		b.transform.position = myPosition;
		b.transform.localScale = new Vector3(0.1f,0.1f,0.1f);
	}

	public void setStartPosition(int temp_x, int temp_z) {
		//float rx = Random.Range (-1.0f, 1.0f);
	//	float ry = Random.Range (-1.0f, 1.0f);
	//	float rz = Random.Range (-1.0f, 1.0f);
		float rvx = Random.Range (-0.01f, 0.01f);
		float rvy = Random.Range (-0.01f, 0.01f);
		float rvz = Random.Range (-0.01f, 0.01f);
		Vector3 vel = new Vector3 (rvx,rvy,rvz);
		Vector3 pos = new Vector3 ((float)temp_x,0.0f,(float)temp_z);
		myPosition = pos;
		myVelocity = vel;
		b.transform.position = myPosition;
		float rcr = Random.Range (0.0f, 1.0f);
		float rcb = Random.Range (0.0f, 1.0f);
		float rcg = Random.Range (0.0f, 1.0f);
		Color myColor = new Color(rcr,rcg,rcb,1);
		b.GetComponent<Renderer>().material.color = myColor;

	}

	public void updatePosition() {
		b.transform.Translate(myVelocity);
		life--;
	}
	public bool isDead() {
		if (life <= 0) {
			return true;
		} else {
			return false;
		}
	}
	public void killParticle(){
		Destroy (b,0);
	}
}