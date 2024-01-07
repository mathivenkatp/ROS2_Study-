#!/usr/bin/env python3
import rclpy
from rclpy.callback_groups import CallbackGroup
from rclpy.node import Node

from example_interfaces.msg import Int64


class numberCounterNode(Node):
    def __init__(self):
        super().__init__("number_counter")
        self.counter_ = 0
        self.subscriber_ = self.create_subscription(
            Int64, "number_publish", self.callback_number_count, 10
        )
        self.get_logger().info("Counter node Startted")

    def callback_number_count(self, msg):
        self.counter_ += msg.data
        self.get_logger().info(str(self.counter_))


def main(args=None):
    rclpy.init(args=args)
    node = numberCounterNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
