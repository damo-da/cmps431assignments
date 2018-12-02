#ifndef PAGING_H
#define PAGING_H

#define FRAME_SIZE 5
#define PAGE_SIZE 100

#include <iostream>
#include <vector>
#include <array>

typedef std::array<int, FRAME_SIZE> Memory;

std::vector<int> readPagingAddresses(std::ifstream&);
void openFile(std::ifstream&, char* name);

void applyAlgorithm(std::vector<int>, int);

Memory initRAM();
bool alreadyInRAM(Memory&, int);
int getIndexOf(Memory&, int);
void printFrameTable(Memory&, bool);

#endif // PAGING_H