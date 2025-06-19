package com.github.javaproblems.codegen;
import java.io.*;
class CodeGen {
    public static void main(String[] args) {
        int chunk1 = new MemoryChunk("Hello World").getMemory();
        System.out.println(chunk1);
    }
}