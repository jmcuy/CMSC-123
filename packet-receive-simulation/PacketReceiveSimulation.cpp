#include <bitset>	
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <cstring>
#include <iostream>
#include <list>
using namespace std;


string constructAddress(string addressLine);
int constructSeqNumber(string seqNumberLine);
string constructCheckSum(string checkSumLine);
int constructDataLength(string dataLengthLine);
string constructData(string dataLine);
string constructPadding(int partialLength);

string convertULongToString(unsigned long sourceInt);
string constructCharacter(string characterLine);
string convertCharToString(char sourceChar);

class Packet {
	public:
		string sourceAddress;
		string destAddress;
		int seqNumber;
		string checkSum;
		int dataLength;
		string data;
		string padding;
		//bool isCorrupted;
		string packetLine;

		Packet();
		Packet(const Packet&);
		Packet(string);

		string constructAddress(string addressLine);
		int constructSeqNumber(string seqNumberLine);
		string constructCheckSum(string checkSumLine);
		int constructDataLength(string dataLengthLine);
		string constructData(string dataLine);
		string constructPadding(int partialLength);

		string convertULongToString(unsigned long sourceInt);
		string constructCharacter(string characterLine);
		string convertCharToString(char sourceChar);
		bool checkSumCorrect();
		string binaryAddition(string sum, string addLine);

};

Packet::Packet() {

}

Packet::Packet(const Packet& copyPacket) {
	sourceAddress = copyPacket.sourceAddress;
	destAddress = copyPacket.destAddress;
	seqNumber = copyPacket.seqNumber;
	checkSum = copyPacket.checkSum;
	dataLength = copyPacket.dataLength;
	data = copyPacket.data;
	padding = copyPacket.padding;
	//isCorrupted = copyPacket.isCorrupted;
	packetLine = copyPacket.packetLine;
}

Packet::Packet(string line) {
	sourceAddress = constructAddress(line.substr(0, 32));
	destAddress = constructAddress(line.substr(32, 32));
	seqNumber = constructSeqNumber(line.substr(64, 16));
	checkSum = constructCheckSum(line.substr(80, 16));
	dataLength = constructDataLength(line.substr(96, 16));
	padding = constructPadding(112 + dataLength);
	packetLine = line;

	if(checkSumCorrect()) {
		data = constructData(line.substr(112, dataLength));
	} else {
		data = "[line corrupted]";
	}
}

string Packet::constructAddress(string addressLine) {
	bitset<8> octet1Bits(addressLine.substr(0, 8));
	bitset<8> octet2Bits(addressLine.substr(8, 8));
	bitset<8> octet3Bits(addressLine.substr(16, 8));
	bitset<8> octet4Bits(addressLine.substr(24, 8));
	unsigned long octet1Int = octet1Bits.to_ulong();
	unsigned long octet2Int = octet2Bits.to_ulong();
	unsigned long octet3Int = octet3Bits.to_ulong();
	unsigned long octet4Int = octet4Bits.to_ulong();
	string octet1 = convertULongToString(octet1Int);
	string octet2 = convertULongToString(octet2Int);
	string octet3 = convertULongToString(octet3Int);
	string octet4 = convertULongToString(octet4Int);

	return octet1 + "." + octet2 + "." + octet3 + "." + octet4;
}

int Packet::constructSeqNumber(string seqNumberLine) {
 	bitset<16> seqNumberBits(seqNumberLine);
 	int seqNumber = (int) seqNumberBits.to_ulong();
 	return seqNumber;
}

string Packet::constructCheckSum(string checkSumLine) {
	return checkSumLine;
}


int Packet::constructDataLength(string dataLengthLine) {
	bitset<16> dataLengthBits(dataLengthLine);
 	int dataLength = (int) dataLengthBits.to_ulong();
 	return dataLength;
}


string Packet::constructData(string dataLine) {
	string data = "";

	for(int i = 0; i < strlen(dataLine.c_str()); i += 8) {
		string character = constructCharacter(dataLine.substr(i, 8));
		data += character;
	}
	return data;
}

string Packet::constructCharacter(string characterLine) {
	bitset<16> characterBit(characterLine);
	char characterChar = (char) ((int) characterBit.to_ulong());
	string character;
	character = convertCharToString(characterChar);

	return character;
}

string Packet::constructPadding(int partialLength) {
	if(partialLength % 16 != 0) {
		return "00000000";
	} else {
		return "";
	}
}

string Packet::convertULongToString(unsigned long sourceInt) {
	stringstream ss;
	ss << sourceInt;
	string destString;
	ss >> destString;
	return destString;
}

string Packet::convertCharToString(char sourceChar) {
	stringstream ss;
	ss << sourceChar;
	string destString;
	destString = ss.str();
	return destString;

}

bool Packet::checkSumCorrect() {
	string dataLine = packetLine + padding;
	dataLine.replace(80, 16, "0000000000000000");
	string sum = "0";
	int totalLength = dataLine.length();

	for(int i = 0; i < totalLength; i += 16) {
		sum = binaryAddition(sum, dataLine.substr(i, 16));
	}

	for(int i = 0; i < sum.length(); i++) {
		if(sum[i] == '0') {
			sum[i] = '1';
		} else {
			sum[i] = '0';
		}
	}
	sum = sum.substr(1, 16);

	return sum.compare(checkSum) == 0;
}

string Packet::binaryAddition(string sum, string addLine) {
	bitset<17> sumBits(sum);
	bitset<17> addLineBits(addLine);
	
	long sumLong = (long) sumBits.to_ulong();
	long addLineLong = (long) addLineBits.to_ulong();
	long totalLong = sumLong + addLineLong;

	bitset<17> totalBits(totalLong);
	string totalString = totalBits.to_string<char,std::string::traits_type,std::string::allocator_type>();

	if(totalString[0] == '1') {
		totalString[0] = '0';

		bitset<17> totalBits(totalString);
		bitset<17> overflow(1);

		long totalLong = (long) totalBits.to_ulong();
		long overflowLong = (long) overflow.to_ulong();
		totalLong = totalLong + overflowLong;

		bitset<17> totalBits2(totalLong);
		totalString = totalBits2.to_string<char,std::string::traits_type,std::string::allocator_type>();
	}

	return totalString;
}

int main () {
	list<list<Packet> > poemList;

	//Receive Packets
	string line;
	ifstream inputFile("inputFile.in");
	if(inputFile.is_open()) {
		while(getline(inputFile, line)) {
			/////////////////////add packet////////////////////////
			Packet newPacket(line);
			list<list<Packet> >::iterator it = poemList.begin();
			while(it != poemList.end() && // infinte loop here
		 		 (it->front().sourceAddress.compare(newPacket.sourceAddress) != 0 || 
		  		  it->front().destAddress.compare(newPacket.destAddress) != 0)) 
			{
				it++;
			}

			
			if(it != poemList.end()) {
			//Find the index to insert packet to respective poem
				list<Packet>::iterator itx2 = it->begin();
				while(itx2 != it->end() && itx2->seqNumber < newPacket.seqNumber) {
					itx2++;
				}
				if(itx2->seqNumber != newPacket.seqNumber) {
					it->insert(itx2, newPacket);
				}
			} else {
				list<Packet> newList;
				newList.push_back(newPacket);
				poemList.push_back(newList);
			}
			///////////////////////////////////////////////////////
		}
		inputFile.close();
	} else {
		cout << "Unable to open file";
	}

	//Data Reconstruction
	ofstream file("poems.in");
	list<list<Packet> >::iterator it = poemList.begin();
	while(it != poemList.end()) {
		list<Packet>::iterator itx2 = it->begin();
		file << itx2->data << endl;
		file << itx2->sourceAddress + "/" + itx2->destAddress << endl;
		itx2++;

		int index = 1;
		while(itx2 != it->end()) {
			if(abs((short)itx2->seqNumber) == index) {
				file << itx2->data << endl;
				itx2++;
			} else {
				file << "[line missing]" << endl;
			}
			index++;
		}
		it++;

		if(it != poemList.end()) {
			file << "--------------------------------------------------------------------------------\n" << endl;
		}
	}
	return 0;
}



