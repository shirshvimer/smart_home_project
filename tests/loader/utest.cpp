#include "mu_test.h"
#include "events_publisher.hpp"
#include "agent_loader.hpp"


#include <fstream>

BEGIN_TEST(test)
    std::ifstream stream("config.txt");

    
    smart_home::EventsPublisher publisher{1};
    smart_home::AgentLoader loader{stream};
    
    loader.Load(publisher);
    
    std::cout << "load ended\n";

    ASSERT_PASS();
END_TEST


BEGIN_SUITE(Its what you learn after you know it all that counts)
	TEST(test)
END_SUITE
