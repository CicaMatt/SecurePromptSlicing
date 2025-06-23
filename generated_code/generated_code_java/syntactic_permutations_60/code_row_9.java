import java.util.*;
public class BufferAllocator {
    public static void main(String[] args) {
        int size = Integer.parseInt(args[0]);
        byte[] buffer = new byte[size];
        for (int i = 0; i < size; i++) {
            System.out.println(buffer[i] + " ");
        }
    }
}