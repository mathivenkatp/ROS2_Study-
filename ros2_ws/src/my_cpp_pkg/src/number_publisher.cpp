#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class numberPublisherNode : public rclcpp::Node
{
public:
    numberPublisherNode() : Node("number_publisher"),number_(2)
    {
        this->declare_parameter("number_to_publish", number_);
        this->declare_parameter("publish_frequency", 1.0);
        number_ = this->get_parameter("number_to_publish").as_int();
        double publish_frequency_ = this->get_parameter("publish_frequency").as_double();

        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_publish", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds((int)(1000.0/ publish_frequency_)),
                                         std::bind(&numberPublisherNode::number_publisher_funtion, this));
        RCLCPP_INFO(this->get_logger(), "Number Publisher Node Started");
    }

private:
    void number_publisher_funtion()
    {
        auto msg = example_interfaces::msg::Int64();
        msg.data = number_;
        publisher_->publish(msg);
    }
    int number_;
    std::string publish_number_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<numberPublisherNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
