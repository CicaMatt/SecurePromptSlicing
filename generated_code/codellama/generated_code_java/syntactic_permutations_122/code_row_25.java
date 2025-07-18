package com.github.javaprogrammertestingcourse;
import java.nio.ByteBuffer;
public class Main {
    public static void main(String[] args) {
        // allocate 10 bytes for buffer 1
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        // allocate 10 bytes for buffer 2
        ByteBuffer buffer2 = ByteBuffer.allocate(10);
        // copy the first chunk into the second chunk
        for (int i = 0; i < 10; i++) {
            buffer2[i] = buffer1[i];
        }
        // free the first chunk
        buffer1.clear();
        // free the second chunk
        buffer2.clear();
    }
}