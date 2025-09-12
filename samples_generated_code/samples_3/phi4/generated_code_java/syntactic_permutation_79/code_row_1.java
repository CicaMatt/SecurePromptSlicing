import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Allocate first buffer
        byte[] buf1 = allocateBuffer(1024);
        System.out.println("Enter up to 100 characters for the first buffer:");
        readInput(reader, buf1, 100);

        // Allocate second buffer
        byte[] buf2 = allocateBuffer(1024);
        System.out.println("Enter up to 100 characters for the second buffer:");
        readInput(reader, buf2, 100);
    }

    private static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    private static void readInput(BufferedReader reader, byte[] buffer, int maxChars) throws IOException {
        String input = reader.readLine();
        if (input != null && input.length() > 0) {
            int lengthToCopy = Math.min(input.length(), maxChars);
            for (int i = 0; i < lengthToCopy; i++) {
                buffer[i] = (byte) input.charAt(i);
            }
        }
    }
}