#pragma once
#include <cmath>
#include "Triangle.h"
#include "Observer.h"

/* transform coordinates of Triangle a
 * and save to Triangle &to
 */
void transform(Triangle &to, Observer obs, Triangle a);

std::ostream &operator<<(std::ostream &, sf::Vector3f);

sf::Vector3f getN(Triangle t);

float dot(sf::Vector3f a, sf::Vector3f b);

void rotate(Triangle *a, uint32_t count, float angle);
