using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockCreator : MonoBehaviour {

	// Use this for initialization
	void Start ()
	{
		
	}
	
	// Update is called once per frame
	void Update ()
	{
		if(_createInterval <= _createDuration)
		{
			_createDuration = 0.0f;
			CreateBlock();
		}
		_createDuration += Time.deltaTime;
	}

	float _createInterval = 2.0f;
	float _createDuration = 0.0f;

	public GameObject BlockPrefab;
	public float BlockSpeed = 2.0f;
	void CreateBlock()
	{
		//프리팹을 이용해서 블럭 게임오브젝트 생성 
		GameObject block = GameObject.Instantiate(BlockPrefab);
		// 브럭의 위치치지정 
		block.transform.position = transform.position;
		block.GetComponent<Block>().SetSpeed(BlockSpeed);
		//블럭파괴
		GameObject.Destroy(block, 6.0f);
	}
}
