#pragma once

struct Vector2
{
  float x,y;
  Vector2() : x(0.f), y(0.f) { }
  Vector2( float ix, float iy ) : x( ix ), y( iy ) { }
  Vector2 operator+( const Vector2& other ) {
    return Vector2( x + other.x, y + other.y );
  }
  Vector2 operator-( const Vector2& other ) {
    return Vector2( x - other.x, y - other.y );
  }
  Vector2& operator+=( const Vector2& other ) {
    x += other.x, y += other.y;
    return *this;
  }
  Vector2& operator-=( const Vector2& other ) {
    x -= other.x, y -= other.y;
    return *this;
  }
};
