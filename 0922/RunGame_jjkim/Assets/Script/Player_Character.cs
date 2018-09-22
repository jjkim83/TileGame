using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player_Character : MonoBehaviour {
	
	
	//유니티 제공하는 함수


	// Use this for initialization
	void Start ()

	{
		ChangeState(eState.IDLE);
	}
	
	// Update is called once per frame
	void Update ()

	{
		
	}
	public enum eState
	{
		IDLE,
		RUN,
	}

	void ChangeState(eState state)
	{
		switch(state)
		{
			case eState.IDLE:
				GetAnimator().SetTrigger("Idle");
				break;
			case eState.RUN:
				GetAnimator().SetTrigger("Run");
				break;
		}
	}


	Animator GetAnimator()
	{
		return gameObject.GetComponent<Animator>();
	}

}
