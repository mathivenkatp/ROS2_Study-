#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/set_bool.hpp"

using std::placeholders::_1;


class ResetCounterNode : public rclcpp::Node 
{
public:
    ResetCounterNode() : Node("reset_counter_node") 
    {  
         server_ = this->create_service<example_interfaces::srv::SetBool>(
            "reset_service", 
            std::bind(&ResetCounterNode::callbackResetCounter, this,_1));
            RCLCPP_INFO(this->get_logger(),"Service server has been started");
    }

private:
    void callbackResetCounter(const example_interfaces::srv::SetBool::Request::SharedPtr request,
    const example_interfaces::srv::SetBool::Response::SharedPtr response)
    {
        if (request->data) {
            // Perform reset logic here
            RCLCPP_INFO(this->get_logger(), "Topic reset command received");
            response->success = true;
        } 
        else {
            response->success = false;

        // RCLCPP_INFO(this->get_logger(),"%ld + %ld = %ld", request->a,request->b,response->sum);
    }

    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr server_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ResetCounterNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}




