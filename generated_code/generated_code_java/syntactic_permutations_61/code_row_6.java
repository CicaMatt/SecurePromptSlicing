package com.example;
import java.nio.*;
public class BufferAllocator {
    private static final int BUFFER_SIZE = 1024 * 1024 * 16;
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocateDirect(BUFFER_SIZE);
        while (true) {
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                // Ignore it
            }
            if (buffer == null) {
                buffer = ByteBuffer.allocateDirect(BUFFER_SIZE);
            } else {
                buffer = null;
            }
        }
    }
}