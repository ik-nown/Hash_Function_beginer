#include <bits/stdc++.h>
#define n 100
#define size 10000
using namespace std;
//hash_table cần xây dựng với độ lớn size=10000
uint32_t hash_table[size];
uint32_t CityHash32(const char *data, size_t len, uint32_t hash)
{   //chuyển đổi con trỏ kiểu dữ liệu char sang con trỏ kiểu dữ liệu uint32_t
    const uint32_t *d = reinterpret_cast<const uint32_t *>(data);
    //khai báo các biến xáo trộn hash truyền vào.
    static uint32_t k0 = 0xdeadbeef;
    static uint32_t k1 = 0x9e3779b9;
    static uint32_t k2 = 0xe6546b64;

    //khai báo h là hash cuối cùng cần trả về sau khi biến đổi.
    uint32_t h = hash;

    //các bước sau là thực hiện xáo trộn hash với các thao tác nhân, xor và dịch bits.
    if (len > 0)
    {
        uint32_t a = *d++;
        h += a * k0;
        h ^= h << 13;
        h *= k1;
    }

    h ^= h >> 16; 
    h *= k2;
    h ^= h >> 13;
    h *= k0;
    h ^= h >> 16;
    h ^= len;
    return h;
}

//hàm tìm index của hash trong hash_table 
//đối số truyền vào là hash vừa tìm được.
size_t IndexInTable(uint32_t hash)
{
    size_t index = hash % size;
    //kiểm tra collision nếu có thì dùng Linear Probing.
    if (hash_table[index]!=0) index=(index+1)%size;
    //gán tại index trong hash table bằng value là hash vừa tạo ra.
    hash_table[index] = hash; 
    return index; //trả về index của hash trong hash table
}
int main()
{   //khai báo và nhập một string nhị phân độ dài không quá 100

    string str = "";
    cin >> str;

    //copy string sang char
    char arr[str.length() + 1];
    strcpy(arr, str.c_str());

    //tìm độ dài của dãy bit nhập vào.
    int len = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (arr[i] != '\0')
            len++;
    }

    //tìm số lần hash (mỗi lần hash 32 bits)
    int length = len / 32;
    if (len % 32 != 0)
        length++;
    //khai báo biến hash 32 bits
    uint32_t hash = 0;

    //biến đánh dấu độ dài còn lại của dãy bits sau mỗi lần băm
    int temp = len;

    //bắt đầu hash với số lần đã tìm trước đó
    for (int i = 0; i < length; i++)
    {   
        //khai báo một mảng char với giá trị khởi tạo là 0
        char arrtmp[32] = {0};

        //xét nếu độ dài dãy còn lại dưới 32 thì cập nhật lại độ dài của mảng char cho phù hợp
        if (temp < 32)
            arrtmp[temp] = {0};
        //sao chép lần lượt bits vào mảng char vừa tạo.
        for (int j = 0; j < len; j++)
        {
            arrtmp[i] = arr[i * 32 + j];
        }
        
        //gọi hàm CityHash32 với các tham số truyền vào như bên dưới.
        //truyền temp như chiều dài
        if (temp<32) hash=CityHash32(arrtmp, temp, hash);
        else hash = CityHash32(arrtmp, 32, hash);
        //cout << hash << " ";
        //cập nhật lại độ dài còn lại của dãy nhị phân chưa hash
        temp -= 32;
    }
    
    //gọi hàm tìm index của hash trong hash_table
    size_t index = IndexInTable(hash);

    //kiểm tra kết quả
    cout << index << endl; 
    cout << hash_table[index];
    return 0;
}
