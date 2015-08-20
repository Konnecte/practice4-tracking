#include "tracker.hpp"

cv::Ptr<Tracker> createTrackerDummy();
cv::Ptr<Tracker> createTrackerMedianFlow();
// TODO: Declare your implementation here
// cv::Ptr<Tracker> createTrackerYourName();

cv::Ptr<Tracker> createTracker(const std::string &impl_name)
{
    if (impl_name == "dummy")
        return createTrackerDummy();
    else if (impl_name == "MedianFlow")
        return createTrackerMedianFlow();
    // TODO: Add case for your implementation
    // else if (impl_name == "your_name"):
    //     return createTrackerYourName();

    return 0;
}
