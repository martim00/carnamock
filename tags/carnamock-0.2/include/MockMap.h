#ifndef INCLUDED_MOCKMAP_H
#define INCLUDED_MOCKMAP_H

namespace carnamock {


	namespace internal {

		std::map<const void*, bool> niceMocks;


		class MockMap
		{
		public:
			static void DisableVerificationsOnMock(const void* mockObject)
			{
				niceMocks[mockObject]= true;	
			}

			static void ClearNiceMock(const void *mockObject)
			{
				niceMocks.erase(mockObject);
			}

			static bool IsNiceMock(const void *mockObject)
			{
				if (niceMocks.find(mockObject) != niceMocks.end())
					return niceMocks[mockObject];
				return false;
			}

		private:
		};



	} //namespace internal

} //namespace carnamock

#endif 