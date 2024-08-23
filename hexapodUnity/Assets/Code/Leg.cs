using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[ExecuteInEditMode]
public class Leg : MonoBehaviour
{
    public bool editMode;
    public GameObject target, pivot1, pivot2, pivot3, leg1, leg2;
    float legLength1, legLength2; 
    public float baseOffset;

    public bool forward;

    void Update()
    {
        if(!editMode && !Application.isPlaying) return;
        moveToPos();
        
    }

    void moveToPos()
    {
        Vector3 pos = target.transform.localPosition; 
        legLength1 = leg1.transform.lossyScale.x; legLength2 = leg2.transform.lossyScale.x;

        float j1 = Mathf.Atan2(-pos.z, pos.x) * Mathf.Rad2Deg + baseOffset; // base angle
        Vector3 angle1 = pivot1.transform.eulerAngles; angle1.y=j1;
        pivot1.transform.eulerAngles=new Vector3(0,j1,0);


        float l = Mathf.Sqrt(pos.x * pos.x + (pos.z * pos.z));
        float h = Mathf.Sqrt(l * l + pos.y * pos.y);
        if(h>legLength1+legLength2)return;

        float phi = Mathf.Atan(pos.y/l) * Mathf.Rad2Deg;
        
        float theta1 = Mathf.Acos(Mathf.Clamp(((legLength1*legLength1)+(h*h)-(legLength2*legLength2))/(2*legLength1*h), -1, 1)) * Mathf.Rad2Deg;
        float theta2 = Mathf.Acos(Mathf.Clamp(((legLength1*legLength1)+(legLength2*legLength2)-(h*h))/(2*legLength1*legLength2), -1, 1)) * Mathf.Rad2Deg;

        float j2 = phi + theta1;
        float j3 = theta2 + 180;
        
        pivot2.transform.localEulerAngles=new Vector3(0,0,j2);
        pivot3.transform.localEulerAngles=new Vector3(0,0,j3);
    }

    public void moveLeg(Vector3 pos) {
        target.transform.localPosition = pos;
    }


    
}
