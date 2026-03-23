import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/jiehuang/xiaoxbot/ros2/xiaox_ws/install/xiaox_driver'
