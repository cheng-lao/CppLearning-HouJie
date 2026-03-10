#include <iostream>
#include <vector>
#include <chrono>
#include <memory_resource>
// https://gemini.google.com/share/9f2eef62d1e4
using namespace std;
using namespace std::chrono;

// 模拟一个包含很多小指针的场景，强制触发海量 malloc/free
void run_final_showdown() {
    const int N = 1000000;

    // --- 1. Default ---
    {
        auto start = high_resolution_clock::now();
        {
            // 模拟 100 万次碎片化分配
            std::vector<int*> v;
            v.reserve(N);
            for(int i=0; i<N; ++i) v.push_back(new int(i));
            
            // 必须手动释放，模拟析构负担
            for(int i=0; i<N; ++i) delete v[i];
        }
        auto end = high_resolution_clock::now();
        cout << "Default (new/delete): " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
    }

    // --- 2. PMR Monotonic ---
    {
        size_t buf_size = 32 * 1024 * 1024; // 32MB
        void* buffer = malloc(buf_size);
        auto start = high_resolution_clock::now();
        {
            std::pmr::monotonic_buffer_resource pool{buffer, buf_size};
            std::pmr::vector<int*> v(&pool);
            v.reserve(N);
            for(int i=0; i<N; ++i) {
                // 在 pool 中分配一个小 int 空间
                int* p = (int*)pool.allocate(sizeof(int));
                *p = i;
                v.push_back(p);
            }
            // 重点：这里不需要循环 delete，pool 销毁时一秒回收
        }
        auto end = high_resolution_clock::now();
        cout << "PMR (Monotonic):      " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
        free(buffer);
    }
}

int main() {
    run_final_showdown();
    return 0;
}