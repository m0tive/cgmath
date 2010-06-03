/// \file Utl.cpp
/// \date 2007/11/19
/// \author Peter Dodds
/// \brief CGM::Utl function definitions
/// \note Copyright (C) 2007 - All Rights Reserved
//------------------------------------------------------------------------------

#include "Utl.hpp"

namespace CGM
{
  bool Utl::PointWithin( const Vector2& subject, Vector2 upper, Vector2 lower, bool sorted /*= true*/ )
  {
    if(!sorted)
    {
      Real temp;
      if(upper.x < lower.x)
      {
        temp = lower.x;
        upper.x = lower.x;
        upper.x = temp;
      }
      if(upper.y < lower.y)
      {
        temp = lower.y;
        upper.y = lower.y;
        upper.y = temp;
      }
    }

    if (subject.x < upper.x && subject.y < upper.y &&
      subject.x > lower.x && subject.y > lower.y)
    {
      return true;
    }
    return false;
  }

  bool Utl::PointWithin(const Vector3& subject, Vector3 upper, Vector3 lower, bool sorted /*= true*/ )
  {
    if(!sorted)
    {
      Real temp;
      if(upper.x < lower.x)
      {
        temp = lower.x;
        upper.x = lower.x;
        upper.x = temp;
      }
      if(upper.y < lower.y)
      {
        temp = lower.y;
        upper.y = lower.y;
        upper.y = temp;
      }
      if(upper.z < lower.z)
      {
        temp = lower.z;
        upper.z = lower.z;
        upper.z = temp;
      }
    }

    if (subject.x < upper.x && subject.y < upper.y && subject.z < upper.z &&
      subject.x > lower.x && subject.y > lower.y && subject.z > lower.z )
    {
      return true;
    }
    return false;
  }

  //------------------------------------------------ Utl::DistanceToLine
  CGM::Real Utl::DistanceToLine( const Vector3& point, const Vector3& lineA, const Vector3& lineB )
  {
    /// \todo Call CGM_SQRT() once, and use Vector3::MagnitudeSquared() rather than Vector3::Magnitude()
#if 1
    CGM::Vector3 AB = lineB - lineA;
    CGM::Real u = ((point - lineA)*AB) / AB.MagnitudeSquared();

    return (point - (lineA + AB*u)).Magnitude();
#else
    return ((lineB - lineA)^(lineA)).Magnitude() / (lineB - lineA).Magnitude();
#endif // 0
  }

  //------------------------------------------------ Utl::DistanceToLineSquared
  CGM::Real Utl::DistanceToLineSquared( const Vector3& point, const Vector3& lineA, const Vector3& lineB )
  {
#if 1
    CGM::Vector3 AB = lineB - lineA;
    CGM::Real u = ((point - lineA)*AB) / AB.MagnitudeSquared();

    return (point - (lineA + AB*u)).MagnitudeSquared();
#else
    return ((lineB - lineA)^(lineA)).MagnitudeSquared() / (lineB - lineA).MagnitudeSquared();
#endif
  }

  //------------------------------------------------ Utl::LineSphereIntersection
  bool Utl::LineSphereIntersection( const Vector3& lineA, const Vector3& lineB, const Vector3& sC, const Real& sR, Vector3* iA, Vector3* iB )
  {
    Real sR_sqrd = sR*sR;
    Real d_sqrd = DistanceToLineSquared(Vector3 (),lineA - sC,lineB - sC);

    if (d_sqrd > sR_sqrd)
      return false;

    Vector3 dirVect = (lineB - lineA).Normalise();

    Real m = CGM_SQRT((sC - lineA).MagnitudeSquared() - d_sqrd);
    Real n = CGM_SQRT(sR_sqrd - d_sqrd);

    *iA = lineA + dirVect * (m - n);
    *iB = lineA + dirVect * (m + n);

    return true;
  }

  //------------------------------------------------ Utl::EstimateRotationBetween
  CGM::Real Utl::EstimateRotationBetween( const Quaternion& A, const Quaternion& B )
  {
    // get the W value of the quaternion between A and B
    // this is DIFF(A,B).w
    // = (B * -A).w
    // only calculate the w component

    return B.w*A.w + B.x*A.x + B.y*A.y + B.z*A.z;
  }

  //------------------------------------------------ Utl::EstimateRotationBetween
  CGM::Real Utl::RotationBetween( const Quaternion& A, const Quaternion& B )
  {
    // get the W value of the quaternion between A and B
    // this is DIFF(A,B).w
    // = (B * -A).w
    // only calculate the w component

    return CGM_ACOS(B.w*A.w + B.x*A.x + B.y*A.y + B.z*A.z) * 2;
  }

  //------------------------------------------------ Utl::ChordToArc
  CGM::Real Utl::ChordToArc( const Real& chord, const Real& radius )
  {
    // chord length calculation:
    //    chord = 2*radius*sin(angle/2)
    //
    // arc length calculation:
    //    arc = angle*radius
    //
    // so, radius is fixed, angle varies. angle in respect to chord:
    //    angle = 2*asin(chord/2*radius)
    //
    // placing this in the arc equation:
    //    arc = 2*radius*asin(chord/2*radius)

    return 2 * radius * CGM_ASIN (chord / (2*radius));
  }

  //------------------------------------------------ Utl::ArcToChord
  CGM::Real Utl::ArcToChord( const Real& arc, const Real& radius )
  {
    // chord length calculation:
    //    chord = 2*radius*sin(angle/2)
    //
    // arc length calculation:
    //    arc = angle*radius
    //
    // so, radius is fixed, angle varies. angle in respect to arc:
    //    angle = arc/radius
    //
    // placing this in the chord equation:
    //    chord = 2*radius*sin(arc/2*radius)

    return 2 * radius * CGM_SIN (arc / (2*radius));
  }

  //------------------------------------------------ Utl::ChordToAngle
  CGM::Real Utl::ChordToAngle( const Real& chord, const Real& radius )
  {
    // chord length calculation:
    //    chord = 2*radius*sin(angle/2)
    //
    // angle in respect to chord:
    //    angle = 2*asin(chord/2*radius)

    return 2 * CGM_ASIN (chord / (2*radius));
  }

  //------------------------------------------------ Utl::ArcToAngle
  CGM::Real Utl::ArcToAngle( const Real& arc, const Real& radius )
  {
    // arc length calculation:
    //    arc = angle*radius
    //
    // angle in respect to arc:
    //    angle = arc/radius

    return arc / radius;
  }

  //------------------------------------------------ Utl::DistanceToLineSegment
  bool Utl::DistanceToLineSegment( const Vector3& point, const Vector3& lineA, const Vector3& lineB, Real& distance )
  {
    if (lineA == lineB)
      return false;

    CGM::Vector3 AB = lineB - lineA;
    CGM::Real u = ((point - lineA)*AB) / AB.MagnitudeSquared();

    if (u > 1 || u < 0)
      return false;

    distance = (point - (lineA + AB*u)).Magnitude();

    return true;
  }

  //------------------------------------------------ Utl::DistanceToLineSegmentSquared
  bool Utl::DistanceToLineSegmentSquared( const Vector3& point, const Vector3& lineA, const Vector3& lineB, Real& distance_squared )
  {
    if (lineA == lineB)
      return false;

    CGM::Vector3 AB = lineB - lineA;
    CGM::Real u = ((point - lineA)*AB) / AB.MagnitudeSquared();

    if (u > 1 || u < 0)
      return false;

    distance_squared = (point - (lineA + AB*u)).Magnitude();

    return true;
  }
}
