// Server side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

const int PORT = 2023;

// binary threshold levels
int N = 11;

// helper function:
// finds a cosine of angle between std::vectors
// from pt0->pt1 and from pt0->pt2
static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
static void findSquares(const cv::Mat& image, std::vector<std::vector<cv::Point>>& squares )
{
    squares.clear();

    // Mat pyr, timg, gray0(image.size(), CV_8U), gray;
    cv::Mat pyr, timg, gray0, gray;

    // down-scale and upscale the image to filter out the noise
    cv::pyrDown(image, pyr, cv::Size(image.cols/2, image.rows/2));
    cv::pyrUp(pyr, timg, image.size());
    std::vector<std::vector<cv::Point>> contours;
    // to grayscale
    cv::cvtColor(timg, gray0, cv::COLOR_BGR2GRAY);
    
    // try several threshold levels
    for( int l = 1; l < N; l++ )
    {
        //to binary image
        cv::threshold(gray0, gray, l*255/N, 255, cv::THRESH_BINARY);

        //find contours and store them all as a list
        cv::findContours(gray, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

        std::vector<cv::Point> approx;

        // test each contour
        for( size_t i = 0; i < contours.size(); i++ )
        {
            // approximate contour with accuracy proportional
            // to the contour perimeter
            cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);

            // square contours should have 4 vertices after approximation
            // relatively large area (to filter out noisy contours)
            // and be convex.
            // Note: absolute value of an area is used because
            // area may be positive or negative - in accordance with the
            // contour orientation
            if( approx.size() == 4 &&
                std::abs(cv::contourArea(cv::Mat(approx))) > 1000 &&
                cv::isContourConvex(cv::Mat(approx)) )
            {
                double maxCosine = 0;

                for( int j = 2; j < 5; j++ )
                {
                    // find the maximum cosine of the angle between joint edges
                    double cosine = std::abs(angle(approx[j%4], approx[j-2], approx[j-1]));
                    maxCosine = MAX(maxCosine, cosine);
                }

                // if cosines of all angles are small
                // (all angles are ~90 degree) then write quandrange
                // vertices to resultant sequence
                if( maxCosine < 0.3 )
                    squares.push_back(approx);
            }
        }
    }
}


// the function draws all the squares in the image
static void drawSquares( cv::Mat& image, const std::vector<std::vector<cv::Point> >& squares )
{
    for( size_t i = 0; i < squares.size(); i++ )
    {
        const cv::Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        cv::polylines(image, &p, &n, 1, true, cv::Scalar(0,255,0), 3, cv::LINE_AA);
    }
}

int main(int argc, char const* argv[])
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	// Creating socket file descriptor
	if (server_fd < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
    int opt = 1;
    int res = setsockopt(
        server_fd, 
        SOL_SOCKET,
		SO_REUSEADDR | SO_REUSEPORT, 
        &opt,
		sizeof(opt)
    );
	if (res < 0) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
    struct sockaddr_in address;
    int addrlen = sizeof(address);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
    res = bind(
        server_fd, 
        (struct sockaddr*)&address,
		sizeof(address)
    );
	if (res	< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

    res = listen(server_fd, 3);
	if (res < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

    int new_socket = accept(
        server_fd, 
        (struct sockaddr*)&address,
		(socklen_t*)&addrlen
    );
	if (new_socket < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

    char buffer[1024] = { 0 };
	int valread = read(new_socket, buffer, 1024);
	std::cout << "msg from client: " << buffer << '\n';

    std::string head = "HTTP/1.1 200 OK\n" \
                    "Content-Type: multipart/x-mixed-replace; boundary=--7b3cc56e5f51db803f790dad720ed50a\n";
	send(new_socket, head.c_str(), head.size(), 0);

    cv::VideoCapture cap(2); 
    // Check if camera opened successfully
    if(!cap.isOpened()){
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    cv::Mat frame;
    while(true){
        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        std::vector<std::vector<cv::Point> > squares;
        findSquares(frame, squares);
        drawSquares(frame, squares);

        std::vector<int> params;
        params.push_back( cv::IMWRITE_JPEG_QUALITY );
        params.push_back( 100 );
        //Вектор для хранения сжатого изображения
        std::vector<uchar> buf;

        // Кодируем изображение с заданной степенью сжатия
        cv::imencode(".jpg", frame, buf, params);
        // Размер сжатого изображения в байтах
        int n = buf.size();
        std::string resp =  "\n--7b3cc56e5f51db803f790dad720ed50a\n" \
                            "Content-Type: image/jpeg\nContent-Length: ";
        resp += std::to_string(n);
        resp += "\n\n";
        send(new_socket, resp.c_str(), resp.size(), 0);
        send(new_socket, (char*)buf.data(), buf.size(), 0);
    }
    cap.release();

	// closing the connected socket
	close(new_socket);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
    close(server_fd);
	return 0;
}
