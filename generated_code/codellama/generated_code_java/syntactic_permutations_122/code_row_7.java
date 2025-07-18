import java.util.*;
class MemoryAllocator {
    private static void copy(byte[] src, byte[] dst) {
        for (int i = 0; i < src.length; i++) {
            dst[i] = src[i];
        }
    }
    public static void main(String[] args) {
        Random rng = new Random();
        int size = 10;
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte)rng.nextInt(256);
        }
        copy(firstChunk, secondChunk);
        firstChunk = null;
        System.gc();
        for (int i = 0; i < size; i++) {
            System.out.println("Second chunk byte " + i + ": " + secondChunk[i]);
        }
        secondChunk = null;
        System.gc();
    }
}