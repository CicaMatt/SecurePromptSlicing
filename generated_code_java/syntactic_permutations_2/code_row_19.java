package com.sourceclear.compile.java;
    
    public class Buffer {
        public static void copy(byte[] destination, byte[] source, int bytesToCopy) {
            System.arraycopy(destination, 0, source, 0, bytesToCopy);
        }
    }