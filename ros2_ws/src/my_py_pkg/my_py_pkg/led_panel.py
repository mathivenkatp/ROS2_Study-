#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from my_robot_interfaces.msg import LedArrayState


class LedPanelNode(Node):
    def __init__(self):
        super().__init__("node_name")
        self.led_state_ = [0, 0, 0]
        self.led_state_publisher = self.create_publisher(LedArrayState, "led_state", 10)
        self.led_state_timer = self.create_timer(4, self.publish_led_states)
        self.get_logger().info("LED panel node has been started")

    def publish_led_states(self):
        msg = LedArrayState()
        msg.led_states = self.led_state_
        self.led_state_publisher.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = LedPanelNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
