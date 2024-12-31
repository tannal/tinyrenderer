#include "tgaimage.h"
#include "geometry.h"

const TGAColor white = TGAColor{255, 255, 255, 255};
const TGAColor red   = TGAColor{255, 0,   0,   255};

void triangle(vec2 t0, vec2 t1, vec2 t2, TGAImage &image, TGAColor color) {
    // 按y坐标排序顶点，确保 t0.y <= t1.y <= t2.y
    if (t0.y > t1.y) std::swap(t0, t1);
    if (t0.y > t2.y) std::swap(t0, t2);
    if (t1.y > t2.y) std::swap(t1, t2);
    
    int total_height = t2.y - t0.y;
    
    // 绘制下半部分三角形
    for (int y = t0.y; y <= t1.y; y++) {
        int segment_height = t1.y - t0.y + 1;
        if (segment_height == 0) continue;
        
        float alpha = (float)(y - t0.y) / total_height;
        float beta  = (float)(y - t0.y) / segment_height;
        
        vec2 A = t0 + (t2 - t0) * alpha;
        vec2 B = t0 + (t1 - t0) * beta;
        
        if (A.x > B.x) std::swap(A, B);
        
        // 绘制扫描线
        for (int x = (int)A.x; x <= (int)B.x; x++) {
            image.set(x, y, color);
        }
    }
    
    // 绘制上半部分三角形
    for (int y = t1.y; y <= t2.y; y++) {
        int segment_height = t2.y - t1.y + 1;
        if (segment_height == 0) continue;
        
        float alpha = (float)(y - t0.y) / total_height;
        float beta  = (float)(y - t1.y) / segment_height;
        
        vec2 A = t0 + (t2 - t0) * alpha;
        vec2 B = t1 + (t2 - t1) * beta;
        
        if (A.x > B.x) std::swap(A, B);
        
        // 绘制扫描线
        for (int x = (int)A.x; x <= (int)B.x; x++) {
            image.set(x, y, color);
        }
    }   
}

int main(int argc, char** argv) {
    const int width = 1024;
    const int height = 1024;
    
    TGAImage image(width, height, TGAImage::RGB);
    
    // 定义三角形顶点
    vec2 t0{10, 10};
    vec2 t1{1000, 100};
    vec2 t2{1000, 1000};
    
    // 绘制三角形
    triangle(t0, t1, t2, image, white);
    
    // 保存结果
    image.flip_vertically(); // 因为TGA格式原点在左下角
    image.write_tga_file("triangle.tga");
    
    return 0;
}