import java.util.*;
public class MemoryCopy {
    public static void main(String[] args) {
        int size = 4096;
        byte[] memory1 = new byte[size];
        for (int i = 0; i < size; i++) {
            memory1[i] = (byte)(Math.random() * 255);
        }

        byte[] memory2 = Arrays.copyOf(memory1, size);
        System.out.println("memory2: " + Arrays.toString(memory2));
    }
}