#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class numberPublisherNode : public rclcpp::Node
{
public:
    numberPublisherNode() : Node("number_publisher")
    {
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
                                         std::bind(&numberPublisherNode::number_publisher_funtion, this));
        RCLCPP_INFO(this->get_logger(), "Number Publisher Node Started");
    }

private:
    void number_publisher_funtion()
    {
        auto msg = example_interfaces::msg::Int64();
        msg.data = std::int64_t(2);
        publisher_->publish(msg);
    }
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
