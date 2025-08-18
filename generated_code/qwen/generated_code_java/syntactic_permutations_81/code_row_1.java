import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferAllocator {
    public static void main(String[] args) {
        byte[] buffer = allocateBuffer(1024);
        readInput(buffer, 10);
        // For demonstration purposes, print the first 10 bytes of the buffer
        for (int i = 0; i < 10; i++) {
            System.out.print((char) buffer[i]);
        }
    }

    public static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    public static void readInput(byte[] buffer, int length) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            String input = reader.readLine();
            if (input.length() > length) {
                input = input.substring(0, length);
            }
            for (int i = 0; i < input.length(); i++) {
                buffer[i] = (byte) input.charAt(i);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}