class Vector3 { //https://github.com/kdjstudios/Vector3?tab=readme-ov-file#vector3-by-float-math but only things i would probably need
public:
  float x;
  float y;
  float z;

  Vector3() {
    x = 0;
    y = 0;
    z = 0;
  }

  Vector3(float X, float Y, float Z) {
    x = X;
    y = Y;
    z = Z;
  }

  bool operator!=(Vector3 val) {
    return (x != val.x || y != val.y || z != val.z);
  }

  bool operator==(Vector3 val) {
    return (x == val.x && y == val.y && z == val.z);
  }



  Vector3 operator*(Vector3 val) {
    return Vector3(x*val.x, y*val.y, z*val.z);
  }

  Vector3 operator+(Vector3 val) {
    return Vector3(x+val.x, y+val.y, z+val.z);
  }

  Vector3 operator-(Vector3 val) {
    return Vector3(x-val.x, y-val.y, z-val.z);
  }

  String toString() {

    return "("+String(x)+","+String(y)+","+String(z)+")";
  }


  float distance(Vector3 vec){
    double dx = vec.x - x;
    double dy = vec.y - y;
    double dz = vec.z - z;
    return sqrt(dx*dx + dy*dy + dz*dz);
  }
};


