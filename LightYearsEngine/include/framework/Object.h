#pragma once

namespace ly{
	class Object
	{
	public:
		Object();
		virtual ~Object();

		void Destory();
		bool isPendingObject() const { return mIsPendingObject; }
	private:
		bool mIsPendingObject;
	};
}
