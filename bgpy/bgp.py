import struct

class BGPPacket(object):
    type_mapping = {1:BGPOpen, 2:BGPUpdate, 3:BGPNotification, 4:BGPKeepAlive}
    pack_format = "10x"

    def __init__(self):
        self.marker = 0
        self.length = 0
        self.message = None

    @property
    def type(self):
        if self.message == None:
            return None

    def to_binary(self):
        message_type = 
        binary = struct.pack(self.pack_format, self.marker, 
                             self.length, self.type)
        

    def from_binary(self):
        pass

class BGPOpen(object):
    pass

class BGPUpdate(object):
    pass

class BGPKeepAlive(object):
    pass

class BGPNotification(object):
    pass

class 
