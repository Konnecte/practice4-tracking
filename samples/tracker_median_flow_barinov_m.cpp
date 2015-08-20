#include <tracker.hpp>

class TrackerMedianFlow : public Tracker
{
 public:
    virtual ~TrackerMedianFlow() {}

    virtual bool init( const cv::Mat& frame, const cv::Rect& initial_position );
    virtual bool track( const cv::Mat& frame, cv::Rect& new_position );

 private:
    cv::Rect position_;
};

bool TrackerMedianFlow::init( const cv::Mat& frame, const cv::Rect& initial_position )
{
    position_ = initial_position;
	return true;
}

bool TrackerMedianFlow::track( const cv::Mat& frame, cv::Rect& new_position )
{
    new_position = position_;
	return true;
}

cv::Ptr<Tracker> createTrackerMedianFlow()
{
    return cv::Ptr<Tracker>(new TrackerMedianFlow());
}
