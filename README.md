# EE450-Programming-Assignment
1) Yuhang Zhang 
2) USC ID:5793680430 
3) Ubuntu 22.04
4) write three files, do CRC check and 2D parity check
5) write crc_rx.cc which read data and return codeword and CRC
   write crc_tx.cc which run CRC algorithum and judge the return with data in dataRx.txt
   write crc_vs_parity2d.cc which do operation based on 2D parity check and CRC, comparing the result from two operation with data in dataVs.txt
6) in crc_vs_parity2d.cc, the program will fail if the input is not 64 bits
   in crc_tx.cc, the generator is CRC16_CCITT by default.
7) the file reading part in crc_rx.cc is generate from chatGPT.