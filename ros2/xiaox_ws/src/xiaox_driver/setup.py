from setuptools import setup

package_name = 'xiaox_driver'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', ['launch/driver.launch.py']),
        ('share/' + package_name + '/config', ['config/serial_port.yaml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='jiehuang',
    maintainer_email='hydrangeahuman@gmail.com',
    description='Serial driver node for Xiaox robot arm firmware communication',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'driver_node = xiaox_driver.driver_node:main',
        ],
    },
)
