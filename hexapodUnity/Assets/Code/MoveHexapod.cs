using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveHexapod : MonoBehaviour
{
    public Leg[] legs = new Leg[6];
    public int gaitID; // 0: Tripod, 1: Bipod, 2: Ripple
    public float speed;
    

    // bezier curve coords
    Vector3 b0 = new Vector3(2,-1.5f,1);
    Vector3 b1 = new Vector3(2,-0.5f, 0.5f); 
    Vector3 b2 = new Vector3(2, -1.5f,-1);

    int frame = 0;
    
    void Start(){
        switch(gaitID){
            case 0:
                for (int i = 0; i<legs.Length; i++){
                    legs[i].forward=i%2==0;
                    // if(i>2)legs[i].forward=!legs[i].forward;
                }
            break;
            case 1:
                for (int i = 0; i<legs.Length; i++){
                    legs[i].forward=false;
                }
            break;
        }

    }
    void FixedUpdate(){
        for(int i = 0; i < legs.Length; i++){
            float t =  Mathf.PingPong(frame * speed/100, 1); 

            Vector3 bezierPoint = Mathf.Pow(1 - t, 2) * b0 + 2 * (1 - t) * t * b1 + Mathf.Pow(t, 2) * b2;
            Vector3 linearPoint = (1 - t) * b0 + t * b2;

            Vector3 newPoint = legs[i].forward?linearPoint:bezierPoint;
            switch(gaitID){
                case 0:
                    if(i!=1&&i!=4)newPoint.z*=-1;
                break;
                case 1:

                break;
            }
            legs[i].target.transform.localPosition = newPoint;

            if (t==1||t==0) legs[i].forward = !legs[i].forward;

        }

        frame++;
       
    }
}
