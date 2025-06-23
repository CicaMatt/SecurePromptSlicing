package com.moringa.codegen;
    import java.util.Arrays;
    public class Main {
      public static void main(String[] args) {
        int[] firstChunk = new int[5];
        int[] secondChunk = new int[10];
        System.out.println("Contents of first chunk: " + Arrays.toString(firstChunk));
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);
        System.out.println("Contents of second chunk: " + Arrays.toString(secondChunk));
      }
    }