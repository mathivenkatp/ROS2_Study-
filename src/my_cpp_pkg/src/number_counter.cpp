#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class numberCounterNode : public rclcpp::Node
{
public:
    numberCounterNode() : Node("number_counter"), publish_counted_number_(0)
    {
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_counter", 10);
        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10,
            std::bind(&numberCounterNode::callbackCounter, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "Number Counter Node Started.");
    }

private:
    void callbackCounter(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        publish_counted_number_ += msg->data;
        auto new_msg = example_interfaces::msg::Int64();
        new_msg.data = publish_counted_number_;
        publisher_->publish(new_msg);
        RCLCPP_INFO(this->get_logger(), "%d", publish_counted_number_);
    }

    int publish_counted_number_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<numberCounterNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
