#!/usr/bin/python
from mininet.topo import Topo
from mininet.net import Mininet
from mininet.node import Node
from mininet.log import setLogLevel
from mininet.cli import CLI


class LinuxRouter(Node):
    def config(self, **params):
        super(LinuxRouter, self).config(**params)
        self.cmd('sysctl net.ipv4.ip_forward=1')

    def terminate(self):
        self.cmd('sysctl net.ipv4.ip_forward=0')
        super(LinuxRouter, self).terminate()


class NetworkTopo(Topo):
    def build(self, **_opts):
        router = self.addHost("r1", ip="10.0.0.1/24", mac="00:00:00:00:fa:ce", cls=LinuxRouter)

        switch = self.addSwitch("s1")

        h1 = self.addHost("h1", ip="10.0.0.10/24", mac="00:00:00:00:00:01", defaultRoute="via 10.0.0.1")
        h2 = self.addHost("h2", ip="10.0.0.20/24", mac="00:00:00:00:00:02", defaultRoute="via 10.0.0.1")

        self.addLink(router, switch)
        self.addLink(h1, switch)
        self.addLink(h2, switch)

def run():
    topo = NetworkTopo()
    net = Mininet(topo=topo)
    net.start()
    CLI(net)
    net.stop()


if __name__ == '__main__':
    setLogLevel('info')
    run()