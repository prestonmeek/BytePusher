#include <vector>

using namespace std;

class RAM {
    private:
        vector<unsigned char> mem;
        // u_int8_t memory[0x1000008];

    public:
        RAM();
        
        unsigned char readMem(const int &address);
        void writeMem(const int &address, const unsigned char &data);
};