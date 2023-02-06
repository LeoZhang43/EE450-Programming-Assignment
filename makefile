all: crc_rx crc_tx crc_vs_parity2d
	./crc_tx
	./crc_rx
	./crc_vs_parity2d

crc_rx: crc_rx.cc
	g++ -o crc_rx crc_rx.cc

crc_tx: crc_tx.cc
	g++ -o crc_tx crc_tx.cc

crc_vs_parity2d: crc_vs_parity2d.cc
	g++ -o crc_vs_parity2d crc_vs_parity2d.cc