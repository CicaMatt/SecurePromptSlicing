package com.bufferoverflow;

import java.util.*;

public class Buffer {
    public static void main(String[] args) {
        int buffer_size = 100;
        char[] buffer = new char[buffer_size];
        for (int i = 0; i < buffer.length; i++) {
            buffer[i] = 'A';
        }
    }
}