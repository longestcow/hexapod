using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Target : MonoBehaviour
{
    // Start is called before the first frame update
    public float speed;
    public Rigidbody rb;

    // Update is called once per frame
    void Update()
    {
        rb.velocity = new Vector3(Input.GetAxisRaw("Horizontal") * speed, 
        (Input.GetKey(KeyCode.LeftShift) ? -1 : (Input.GetKey(KeyCode.Space))? 1 : 0) * speed, 
        Input.GetAxisRaw("Vertical") * speed);
    }
}
