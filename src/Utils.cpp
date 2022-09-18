#include "Utils.h"

void transform(Triangle &to, Observer obs, Triangle a)
{
  to.color = a.color;
  float sqrtp2 = sqrt(obs.pointing.y*obs.pointing.y + obs.pointing.x*obs.pointing.x);
  float lx = - obs.pointing.y / sqrtp2;
  float ly = obs.pointing.x / sqrtp2;
  float mx = - (obs.pointing.x * obs.pointing.z) / sqrtp2;
  float my = - (obs.pointing.y * obs.pointing.z) / sqrtp2;
  float mz = sqrtp2;

  to.A = a.A - obs.pos;
  to.B = a.B - obs.pos;
  to.C = a.C - obs.pos;

  to.A.x = obs.pointing.x * to.A.x +
          obs.pointing.y * to.A.y +
          obs.pointing.z * to.A.z;
  to.A.y = lx * to.A.x + ly * to.A.y;
  to.A.z = mx * to.A.x + my * to.A.y + mz * to.A.z;

  to.B.x = obs.pointing.x * to.B.x +
          obs.pointing.y * to.B.y +
          obs.pointing.z * to.B.z;
  to.B.y = lx * to.B.x + ly * to.B.y;
  to.B.z = mx * to.B.x + my * to.B.y + mz * to.B.z;

  to.C.x = obs.pointing.x * to.C.x +
          obs.pointing.y * to.C.y +
          obs.pointing.z * to.C.z;
  to.C.y = lx * to.C.x + ly * to.C.y;
  to.C.z = mx * to.C.x + my * to.C.y + mz * to.C.z;
}

std::ostream &operator<<(std::ostream &os, sf::Vector3f a)
{
  os << a.x << " " << a.y << " " << a.z;
  return os;
}

sf::Vector3f getN(Triangle t)
{
  sf::Vector3f AB = t.B - t.A;
  sf::Vector3f AC = t.C - t.A;
  sf::Vector3f n{ AB.y*AC.z - AB.z*AC.y,
                  AB.z*AC.x - AB.x*AC.z,
                  AB.x*AC.y - AB.y*AC.x };
  float length = sqrt( n.x*n.x + n.y*n.y + n.z*n.z );
  n.x /= length;
  n.y /= length;
  n.z /= length;
  return n;
}

// float getBrightness(Triangle t, sf::Vector3f b)
// {
//   sf::Vector3f AB = t.B - t.A;
//   sf::Vector3f AC = t.C - t.A;
//   sf::Vector3f n{ AB.y*AC.z - AB.z*AC.y,
//                   AB.z*AC.x - AB.x*AC.z,
//                   AB.x*AC.y - AB.y*AC.x };
//   float length = sqrt( n.x*n.x + n.y*n.y + n.z*n.z );
//   n.x /= length;
//   n.y /= length;
//   n.z /= length;
//   return (n.x*b.x + n.y*b.y + n.z*b.z);
// }
float dot(sf::Vector3f a, sf::Vector3f b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}


void rotate(Triangle *a, uint32_t count, float angle)
{
  float sin0 = sin(angle);
  float cos0 = cos(angle);
  float tmpx, tmpy;
  for(uint32_t i=0; i<count; i++) {
    tmpx = a[i].A.x;
    tmpy = a[i].A.y;
    a[i].A.x = tmpx*cos0 + tmpy*sin0;
    a[i].A.y = -tmpx*sin0 + tmpy*cos0;

    tmpx = a[i].B.x;
    tmpy = a[i].B.y;
    a[i].B.x = tmpx*cos0 + tmpy*sin0;
    a[i].B.y = -tmpx*sin0 + tmpy*cos0;

    tmpx = a[i].C.x;
    tmpy = a[i].C.y;
    a[i].C.x = tmpx*cos0 + tmpy*sin0;
    a[i].C.y = -tmpx*sin0 + tmpy*cos0;
  }
}
