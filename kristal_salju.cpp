#include <chrono>
#include <functional>
#include <memory>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std;
using namespace std::chrono_literals;

class KristalSalju : public rclcpp::Node
{
public:
  KristalSalju() : Node("kristal_salju")
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    this_thread::sleep_for(1s);
  }

  void move(double speed, double distance, bool forward = true) {
        auto vel_msg = geometry_msgs::msg::Twist();
        vel_msg.linear.x = forward ? abs(speed) : -abs(speed);
        vel_msg.linear.y = 0.0;
        vel_msg.linear.z = 0.0;
        vel_msg.angular.x = 0.0;
        vel_msg.angular.y = 0.0;
        vel_msg.angular.z = 0.0;

        auto t0 = this->now();
        double current_distance = 0.0;

        while (current_distance < distance && rclcpp::ok()) {
            publisher_->publish(vel_msg);
            auto t1 = this->now();
            current_distance = speed * (t1 - t0).seconds();
            this_thread::sleep_for(10ms);
        }

        vel_msg.linear.x = 0.0;
        publisher_->publish(vel_msg);
    }

    void rotate(double speed_deg, double angle_deg, bool clockwise = false) {
        auto vel_msg = geometry_msgs::msg::Twist();
        double speed_rad = speed_deg * M_PI / 180.0;
        double angle_rad = angle_deg * M_PI / 180.0;

        vel_msg.linear.x = 0.0;
        vel_msg.linear.y = 0.0;
        vel_msg.linear.z = 0.0;
        vel_msg.angular.x = 0.0;
        vel_msg.angular.y = 0.0;
        vel_msg.angular.z = clockwise ? -abs(speed_rad) : abs(speed_rad);

        auto t0 = this->now();
        double current_angle = 0.0;

        while (current_angle < angle_rad && rclcpp::ok()) {
            publisher_->publish(vel_msg);
            auto t1 = this->now();
            current_angle = speed_rad * (t1 - t0).seconds();
            this_thread::sleep_for(10ms);
        }

        vel_msg.angular.z = 0.0;
        publisher_->publish(vel_msg);
    }

    void gambar_sisi (double length, int depth, double speed = 1.5) {
        if (depth == 0) {
            move(speed, length);
        } else {
            gambar_sisi (length / 3.0, depth - 1, speed);
            rotate(90, 60, false);
            gambar_sisi (length / 3.0, depth - 1, speed);
            rotate(90, 120, true);
            gambar_sisi (length / 3.0, depth - 1, speed);
            rotate(90, 60, false);
            gambar_sisi (length / 3.0, depth - 1, speed);
        }
    }

    void gambar_KristalSalju(double length = 4.5, int depth = 2) {
        RCLCPP_INFO(this->get_logger(), "Mulai menggambar Kristal Salju");
        
        for (int i = 0; i < 3; ++i) {
            gambar_sisi (length, depth);
            rotate(90, 120, true);
        }
        
        RCLCPP_INFO(this->get_logger(), "Selesai menggambar Kristal Salju!");
    }

private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = make_shared<KristalSalju>();
    
    node->gambar_KristalSalju(4.5, 2);
    
    rclcpp::shutdown();
    return 0;
}