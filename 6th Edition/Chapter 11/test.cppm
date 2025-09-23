module;
#include <iostream>;
export module testModule;

namespace testingNameSpace {
    export class TestClass {
        public:
            void testMethod() {
                std::cout << __FUNCTION__ << '\n';
            }
    };
}