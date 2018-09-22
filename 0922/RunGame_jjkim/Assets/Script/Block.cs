using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Block : MonoBehaviour {
	

	void Start ()

	{
		gameObject.GetComponent<Rigidbody2D>().velocity = new Vector2(-5.0f, 0.0f);
	}
	
	void Update ()

	{
		
	}

	public void SetSpeed(float speed)
	{
		gameObject.GetComponent<Rigidbody2D>().velocity = new Vector2(-speed, 0.0f);
	}

}
