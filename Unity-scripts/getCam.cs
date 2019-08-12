using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class getCam : MonoBehaviour {

	/*
	 * Use this script to get web cam feed and attach the script to 3D primitive 
	 * cube, sphere, capsule, palne

	*/



	private WebCamTexture myWebcamTexture;

	// Use this for initialization
	void Start () {

		// Get available cameras
		WebCamDevice[] myDevices = WebCamTexture.devices;
		for (int i = 0; i < myDevices.Length; i++) {
			Debug.Log (myDevices[i].name);
		}

		// create texture for web cam feed
		 myWebcamTexture = new WebCamTexture();

		// if cam found use the first available cam
		if (myDevices.Length > 0)
		{
			myWebcamTexture.deviceName = myDevices[0].name;
			myWebcamTexture.Play();
		}
	}

	void Update(){

		// use whole array of pixels as raw data
		Color32[] pix = myWebcamTexture.GetPixels32();
		//System.Array.Reverse(pix); // flip image, optional

		//create new texture with same size
		Texture2D destTex = new Texture2D(myWebcamTexture.width, myWebcamTexture.height);
		destTex.SetPixels32(pix);
		destTex.Apply();

		// attach texture to component (this means the primitive that this scpript is attached to)
		GetComponent<Renderer>().material.mainTexture = destTex;	
	}
		
}
