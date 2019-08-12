using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class videoPlayControl : MonoBehaviour {

	public GameObject[] screens;
	public GameObject[] videos;
	private bool[] videosArePlaying = new bool[8];
	private int[] counters = new int[8];
	public int PlayTime = 100;


	// Use this for initialization
	void Start () {

		for (int i = 0; i<counters.Length; i++){
			counters [i] = 0;
		}

		for (int i = 0; i<videosArePlaying.Length; i++){
			videosArePlaying [i] = false;
		}
						
	}
	
	// Update is called once per frame
	void Update () {

		for (int i = 0; i < videos.Length; i++) {
			
			if (videosArePlaying [i]) {
				UnityEngine.Video.VideoPlayer v = videos[i].GetComponent (typeof(UnityEngine.Video.VideoPlayer)) as UnityEngine.Video.VideoPlayer;
				v.name = "Is Playing";
				v.isLooping = true;
				v.Play ();
				screens [i].SetActive (true);

			} else if (!videosArePlaying [i]) {

				UnityEngine.Video.VideoPlayer v = videos[i].GetComponent (typeof(UnityEngine.Video.VideoPlayer)) as UnityEngine.Video.VideoPlayer;
				v.name = "Not Playing";
				v.isLooping = false;
				v.Stop ();

				screens [i].SetActive (false);

			}
		}

		for (int i = 0; i<counters.Length; i++){
			counters [i]++;

			if (counters [i] > PlayTime) {
				videosArePlaying [i] = !videosArePlaying [i];
				counters [i] = 0;
			}
		}




	}


}
