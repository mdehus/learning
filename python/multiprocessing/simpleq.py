import multiprocessing as mp

def process_packet(pktq):
    while True:
        pkt = pktq.get()
        print pkt
        if pkt == 0:
            return

def main():
    pktq = mp.Queue()
    p1 = mp.Process(target=process_packet, args=(pktq,))
    p1.start()
    pktq.put('stuff')
    pktq.put(0)
    p1.join()

    return 1
    

if __name__ == '__main__':
    main()
