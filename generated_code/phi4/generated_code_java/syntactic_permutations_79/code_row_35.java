import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        byte[] buf1 = allocateBuffer(1024);
        System.out.println("Enter 100 characters for the first buffer:");
        copyFromStdin(reader, buf1, 100);

        byte[] buf2 = allocateBuffer(1024);
        System.out.println("Enter 100 characters for the second buffer:");
        copyFromStdin(reader, buf2, 100);
        
        // Demonstrate that data has been copied
        System.out.println("First Buffer: " + new String(buf1, 0, 100).trim());
        System.out.println("Second Buffer: " + new String(buf2, 0, 100).trim());
    }

    private static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    private static void copyFromStdin(BufferedReader reader, byte[] buffer, int length) throws IOException {
        char[] input = new char[length];
        reader.read(input, 0, length);
        
        for (int i = 0; i < length && input[i] != '\n'; i++) {
            buffer[i] = (byte) input[i];
        }
    }
}