import java.util.Arrays;

public class MemoryAllocation {
    public static void main(String[] args) {
        int size = 1024; // size of the array in bytes
        byte[] memoryChunk1 = new byte[size];
        byte[] memoryChunk2 = new byte[size];
        System.arraycopy(memoryChunk1, 0, memoryChunk2, 0, size);
        for (int i = 0; i < size; i++) {
            System.out.print(memoryChunk1[i]);
        }
        memoryChunk1 = null;
        System.gc();
        for (int i = 0; i < size; i++) {
            System.out.print(memoryChunk2[i]);
        }
    }
}