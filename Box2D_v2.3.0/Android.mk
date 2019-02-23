LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libBox2D
LOCAL_SRC_FILES := \
    Dynamics/b2Body.cpp \
    Dynamics/b2Island.cpp \
    Dynamics/Contacts/b2PolygonContact.cpp \
    Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
    Dynamics/Contacts/b2ContactSolver.cpp \
    Dynamics/Contacts/b2Contact.cpp \
    Dynamics/Contacts/b2ChainAndCircleContact.cpp \
    Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
    Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
    Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
    Dynamics/Contacts/b2CircleContact.cpp \
    Dynamics/b2World.cpp \
    Dynamics/Joints/b2WeldJoint.cpp \
    Dynamics/Joints/b2PulleyJoint.cpp \
    Dynamics/Joints/b2GearJoint.cpp \
    Dynamics/Joints/b2DistanceJoint.cpp \
    Dynamics/Joints/b2MouseJoint.cpp \
    Dynamics/Joints/b2PrismaticJoint.cpp \
    Dynamics/Joints/b2FrictionJoint.cpp \
    Dynamics/Joints/b2RevoluteJoint.cpp \
    Dynamics/Joints/b2WheelJoint.cpp \
    Dynamics/Joints/b2MotorJoint.cpp \
    Dynamics/Joints/b2Joint.cpp \
    Dynamics/Joints/b2RopeJoint.cpp \
    Dynamics/b2ContactManager.cpp \
    Dynamics/b2Fixture.cpp \
    Dynamics/b2WorldCallbacks.cpp \
    Rope/b2Rope.cpp \
    Common/b2BlockAllocator.cpp \
    Common/b2Math.cpp \
    Common/b2StackAllocator.cpp \
    Common/b2Settings.cpp \
    Common/b2Timer.cpp \
    Common/b2Draw.cpp \
    Collision/b2CollidePolygon.cpp \
    Collision/b2Distance.cpp \
    Collision/b2Collision.cpp \
    Collision/b2CollideCircle.cpp \
    Collision/b2DynamicTree.cpp \
    Collision/b2BroadPhase.cpp \
    Collision/b2CollideEdge.cpp \
    Collision/Shapes/b2ChainShape.cpp \
    Collision/Shapes/b2EdgeShape.cpp \
    Collision/Shapes/b2PolygonShape.cpp \
    Collision/Shapes/b2CircleShape.cpp \
    Collision/b2TimeOfImpact.cpp

include $(BUILD_STATIC_LIBRARY)
