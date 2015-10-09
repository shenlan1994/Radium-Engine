#ifndef RADIUMENGINE_VECTOR_HPP
#define RADIUMENGINE_VECTOR_HPP

/// This file contains typedefs and basic vector classes and functions

#include <Core/RaCore.hpp>

#include <functional>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <unsupported/Eigen/AlignedVector3>

#include <Core/Math/Math.hpp>

// General config
// Use this to force vec3 to be aligned for vectorization (FIXME not working yet)
// #define CORE_USE_ALIGNED_VEC3

namespace Ra
{
    namespace Core
    {
        //
        // Common vector types
        //

        typedef Eigen::Matrix<Scalar, 4, 1> Vector4;
        typedef Eigen::Vector4f             Vector4f;
        typedef Eigen::Vector4d             Vector4d;

#ifndef CORE_USE_ALIGNED_VEC3
        typedef Eigen::Matrix<Scalar, 3, 1> Vector3;
        typedef Eigen::Vector3f             Vector3f;
        typedef Eigen::Vector3d             Vector3d;
#else
        typedef Eigen::AlignedVector3<Scalar> Vector3;
        typedef Eigen::AlignedVector3<float> Vector3f;
        typedef Eigen::AlignedVector3<double> Vector3d;
#endif

        typedef Eigen::Matrix<Scalar, 2, 1> Vector2;
        typedef Eigen::Vector2f             Vector2f;
        typedef Eigen::Vector2d             Vector2d;

        typedef Eigen::Vector2i Vector2i;
        typedef Eigen::Vector3i Vector3i;
        typedef Eigen::Vector4i Vector4i;

        //
        // Common matrix types
        //

        typedef Eigen::Matrix<Scalar, 4, 4> Matrix4;
        typedef Eigen::Matrix<Scalar, 3, 3> Matrix3;
        typedef Eigen::Matrix<Scalar, 2, 2> Matrix2;

        typedef Eigen::Matrix4f Matrix4f;
        typedef Eigen::Matrix3f Matrix3f;
        typedef Eigen::Matrix2f Matrix2f;

        typedef Eigen::Matrix4d Matrix4d;
        typedef Eigen::Matrix3d Matrix3d;
        typedef Eigen::Matrix2d Matrix2d;

        //
        // Transforms and rotations
        //

        typedef Eigen::Quaternion<Scalar> Quaternion;
        typedef Eigen::Quaternionf        Quaternionf;
        typedef Eigen::Quaterniond        Quaterniond;

        typedef Eigen::Transform<Scalar, 3, Eigen::Affine> Transform;
        typedef Eigen::Affine3f                            Transformf;
        typedef Eigen::Affine3d                            Transformd;

        typedef Eigen::AlignedBox<Scalar, 3> Aabb;
        typedef Eigen::AlignedBox3f          Aabbf;
        typedef Eigen::AlignedBox3d          Aabbd;

        typedef Eigen::AngleAxis<Scalar> AngleAxis;
        typedef Eigen::AngleAxisf        AngleAxisf;
        typedef Eigen::AngleAxisd        AngleAxisd;

        typedef Eigen::Translation<Scalar, 3> Translation;
        typedef Eigen::Translation3f         Translationf;
        typedef Eigen::Translation3d         Translationd;

        // Todo : storage transform using quaternions ?

        /// An oriented bounding box.
        class Obb
        {
        public:
            /// Constructors and destructor.
            Obb() : m_aabb(),  m_transform( Transform::Identity() ) {}
            Obb( const Aabb& aabb, const Transform& tr ) : m_aabb( aabb ), m_transform( tr ) {}
            Obb( const Obb& other ) = default;
            Obb& operator=( const Obb& other ) = default;
            ~Obb() {}

            /// Return the AABB enclosing this
            Aabb toAabb() const;

            /// Extends the OBB with an new point.
            void addPoint( const Vector3& p );
			/// Returns the position of the i^th corner of AABB (model space)
			Vector3 corner(int i) const;

        public:
            /// The untransformed AABB
            Aabb m_aabb;
            /// Orientation of the box.
            Transform m_transform;
        };

        //
        // Misc types
        //
        typedef Vector4 Color;

        //
        // Vector Functions
        //
        namespace Vector
        {
            /// Component-wise floor() function on a floating-point vector.
            template<typename Vector>
            inline Vector floor( const Vector& v );

            /// Component-wise ceil() function on a floating-point vector.
            template<typename Vector>
            inline Vector ceil( const Vector& v );

            /// Component-wise clamp() function on a floating-point vector.
            template<typename Vector>
            inline Vector clamp( const Vector& v, const Vector& min, const Vector& max );

            /// Component-wise clamp() function on a floating-point vector.
            template<typename Vector>
            inline Vector clamp( const Vector& v, const Scalar& min, const Scalar& max );

            /// Vector range check, works for any numeric vector.
            template<typename Vector_>
            inline bool checkRange( const Vector_& v, const Scalar& min, const Scalar& max );

            /// Get two vectors orthogonal to a given vector.
            inline void getOrthogonalVectors( const Vector3& fx, Vector3& fy, Vector3& fz );

            /// Get the angle between two vectors. Works for types where the cross product is
            /// defined (i.e. 2D and 3D vectors).
            template<typename Vector_>
            inline Scalar getAngle( const Vector_& v1, const Vector_& v2);

			/// @return the projection of point on the plane define by planePos and planeNormal
			inline Vector3 projectOnPlane(const Vector3& planePos, const Vector3 planeNormal, const Vector3& point);
			
            /// Get the cotangent of the angle between two vectors. Works vor vector types where
            /// dot and cross product is defined (2D or 3D vectors).
            template <typename Vector_>
            inline Scalar cotan( const Vector_& v1, const Vector_& v2);
        }

        //
        // Quaternion functions
        //

        inline Quaternion operator+ ( const Quaternion& q1, const Quaternion& q2 );
        inline Quaternion operator* ( const Scalar& k, const Quaternion& q );
		inline Quaternion operator/ ( const Quaternion& q, const Scalar& k);

        // Use this macro in the public: section of a class
        // when declaring objects containing Vector or Matrices.
        // http://eigen.tuxfamily.org/dox-devel/group__TopicStructHavingEigenMembers.html
#define  RA_CORE_ALIGNED_NEW EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    }
} // end namespace Ra::Core

#include <Core/Math/LinearAlgebra.inl>

#endif// RADIUMENGINE_VECTOR_HPP

