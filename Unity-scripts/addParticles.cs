using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class addParticles : MonoBehaviour {

	private Particle[] particles;
	private int num;

	// Use this for initialization
	void Start () {
		num = 1000;
		particles = new Particle[num];

		for (int i = 0; i < num; ++i)
		{
			
			particles[i] = new Particle ();
			particles[i].setStartPosition();
		}
	}
	
	// Update is called once per frame
	void Update () {


		for (int i = 0; i < num; ++i)
		{
			if (particles [i].isDead ()) {
				particles [i].killParticle ();
				particles[i] = new Particle ();
				particles[i].setStartPosition();
			} else {
				particles[i].updatePosition ();
			}
		}
	}
}

public class Particle : MonoBehaviour {

	private Vector3 myPosition;
	private Vector3 myVelocity;
	private float life;
	GameObject b;
	Rigidbody rb;

			
	public Particle(){
		b = GameObject.CreatePrimitive (PrimitiveType.Sphere);
		rb = b.AddComponent<Rigidbody>();
		rb.isKinematic=true;
		life = Random.Range (100, 1000);
		b.transform.position = myPosition;
		b.transform.localScale = new Vector3(0.1f,0.1f,0.1f);
	}

	public void setStartPosition() {
		float rx = Random.Range (-1.0f, 1.0f);
		float ry = Random.Range (-1.0f, 1.0f);
		float rz = Random.Range (-1.0f, 1.0f);
		float rvx = Random.Range (-0.01f, 0.01f);
		float rvy = Random.Range (-0.01f, 0.01f);
		float rvz = Random.Range (-0.01f, 0.01f);
		Vector3 vel = new Vector3 (rvx,rvy,rvz);
		Vector3 pos = new Vector3 (rx,ry,rz);
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