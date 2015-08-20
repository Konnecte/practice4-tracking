#include <tracker.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "stdio.h"//
#include "time.h"//
using namespace cv;

cv::Mat old_gray, new_gray;
vector<Point2f> points[2];

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
    cv::cvtColor(frame, old_gray, CV_BGR2GRAY);//1st frame to gray
    Mat submat( old_gray, position_ ); //submat (rect)
    goodFeaturesToTrack(submat, points[1], 500, 0.01, 10, Mat(), 3, 0, 0.04); //good features in rect
    points[0]=points[1];
	return true;
}

bool addRemovePt = false;

bool TrackerMedianFlow::track( const cv::Mat& frame, cv::Rect& new_position )
{
    cv::cvtColor(frame, new_gray, CV_BGR2GRAY);//new frame to gray

    vector<uchar> status;
    vector<float> err;
    TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03);
    calcOpticalFlowPyrLK(old_gray, new_gray, points[0], points[1], status, err, frame.size(),
                                 3, termcrit, 0, 0.001);
            size_t i, k;
                      //      Mat frame2=frame;
            for( i = k = 0; i < points[1].size(); i++ )
            {
                points[1][k++] = points[1][i];

                //circle(frame2, points[1][i], 3, Scalar(0,255,0), -1, 8);
            }
            //
          /*  vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        compression_params.push_back(9);
        imwrite("123.png", frame2, compression_params);*/
//
            points[1].resize(k);

//Вычислить для них optical flow (следует использовать функцию calcOpticalFlowPyrLK, пример использования) и отфильтровать "плохие" точки. Фильтрация "плохих" точек осуществляется следующим образом:
//Отбросить точки, которые не протрекались, у них статус false.
//Выбрать медианную ошибку.
//Назначить "плохими" все точки, для которых ошибка больше медианной.
//Выбрать медианные смещения по X и по Y.

    Mat submat( new_gray, position_ ); //submat (rect)
    goodFeaturesToTrack(submat, points[1], 500, 0.01, 10, Mat(), 3, 0, 0.04); //good features in rect
    old_gray = new_gray;//save new frame to next step
    new_position = position_;//todo
	return true;
}

cv::Ptr<Tracker> createTrackerMedianFlow()
{
    return cv::Ptr<Tracker>(new TrackerMedianFlow());
}
