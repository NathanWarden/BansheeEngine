//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsCorePrerequisites.h"
#include "BsBoxCollider.h"
#include "BsComponent.h"

namespace BansheeEngine 
{
	/** @addtogroup Components-Core
	 *  @{
	 */

	/**
	 * @copydoc	Collider
	 *
	 * Wraps Collider as a Component.
	 */
    class BS_CORE_EXPORT CCollider : public Component
    {
    public:
		CCollider(const HSceneObject& parent);

		/** @copydoc Collider::setIsTrigger */
		inline void setIsTrigger(bool value);

		/** @copydoc Collider::getIsTrigger */
		bool getIsTrigger() const { return mIsTrigger; }

		/** @copydoc Collider::setMass */
		inline void setMass(float mass);

		/** @copydoc Collider::getMass */
		float getMass() const { return mMass; }

		/** @copydoc Collider::setMaterial */
		inline void setMaterial(const HPhysicsMaterial& material);

		/** @copydoc Collider::getMaterial */
		HPhysicsMaterial getMaterial() const { return mMaterial; }

		/** @copydoc Collider::setContactOffset */
		inline void setContactOffset(float value);

		/** @copydoc Collider::getContactOffset */
		float getContactOffset() const { return mContactOffset; }

		/** @copydoc Collider::setRestOffset */
		inline void setRestOffset(float value);

		/** @copydoc Collider::getRestOffset */
		float getRestOffset() const { return mRestOffset; }

		/** @copydoc Collider::setLayer */
		inline void setLayer(UINT64 layer);

		/** @copydoc Collider::getLayer */
		UINT64 getLayer() const { return mLayer; }

		/** @copydoc Collider::getRigidbody */
		HRigidbody getRigidbody() const { return mParent; }

		/** @copydoc Collider::onCollisionBegin */
		Event<void(const CollisionData&)> onCollisionBegin;

		/** @copydoc Collider::onCollisionStay */
		Event<void(const CollisionData&)> onCollisionStay;

		/** @copydoc Collider::onCollisionEnd */
		Event<void(const CollisionData&)> onCollisionEnd;

		/** @cond INTERNAL */

		/** Returns the Collider implementation wrapped by this component. */
		SPtr<Collider> _getInternal() const { return mInternal; }

		/** @endcond */

		/************************************************************************/
		/* 						COMPONENT OVERRIDES                      		*/
		/************************************************************************/
	protected:
		friend class SceneObject;
		friend class CRigidbody;

		/** @copydoc Component::onInitialized() */
		void onInitialized() override;

		/** @copydoc Component::onDestroyed() */
		void onDestroyed() override;

		/** @copydoc Component::onDisabled() */
		void onDisabled() override;

		/** @copydoc Component::onEnabled() */
		void onEnabled() override;

		/** @copydoc Component::onTransformChanged() */
		void onTransformChanged(TransformChangedFlags flags) override;

    protected:
		/** Creates the internal representation of the Collider for use by the component. */
		virtual SPtr<Collider> createInternal() = 0;

		/** Creates the internal representation of the Collider and restores the values saved by the Component. */
		virtual void restoreInternal();

		/** 
		 * Checks is the provided rigidbody a valid parent for this collider. 
		 *
		 * @note This is required because certain colliders are limited in how they can be used. */
		virtual bool isValidParent(const HRigidbody& parent) const { return true; }

		/**
		 * Changes the rigidbody parent of the collider. Meant to be called from the Rigidbody itself. 
		 *
		 * @param rigidbody	New rigidbody to assign as the parent to the collider.
		 * @param internal	If true the rigidbody will just be changed internally, but parent rigidbody will not be
		 *                  notified.
		 */
		void setRigidbody(const HRigidbody& rigidbody, bool internal = false);

		/** 
		 * Updates the transform of the internal Collider representation from the transform of the component's Scene Object.
		 */
		void updateTransform();

		/** Searches the parent scene object hierarchy to find a parent Rigidbody component. */
		void updateParentRigidbody();

		/** Triggered when the internal collider begins touching another object. */
		void triggerOnCollisionBegin(const CollisionData& data);

		/** Triggered when the internal collider continues touching another object. */
		void triggerOnCollisionStay(const CollisionData& data);

		/** Triggered when the internal collider ends touching another object. */
		void triggerOnCollisionEnd(const CollisionData& data);

		SPtr<Collider> mInternal;

		UINT64 mLayer = 1;
		float mRestOffset = 0.0f;
		float mContactOffset = 0.0f;
		HPhysicsMaterial mMaterial;
		float mMass = 0.0f;
		bool mIsTrigger = false;
		Vector3 mLocalPosition;
		Quaternion mLocalRotation;

		HRigidbody mParent;

		/************************************************************************/
		/* 								RTTI		                     		*/
		/************************************************************************/
	public:
		friend class CColliderRTTI;
		static RTTITypeBase* getRTTIStatic();
		RTTITypeBase* getRTTI() const override;

	protected:
		CCollider() {} // Serialization only
     };

	 /** @} */
}