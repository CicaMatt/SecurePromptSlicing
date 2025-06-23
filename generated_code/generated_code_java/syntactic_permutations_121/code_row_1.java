package com.java;
public class HelloWorld{
    public static void main(String[] args){
        System.out.println("Hello, World!");
        int[] memory1 = new int[5];
        int[] memory2 = new int[3];
        System.arraycopy(memory1, 0, memory2, 0, Math.min(memory1.length, memory2.length));
        for (int i : memory2) {
            System.out.print(i + " ");
        }
        memory1 = null;
        System.gc();
        for (int i : memory2) {
            System.out.print(i + " ");
        }
        memory2 = null;
        System.gc();
    }
}