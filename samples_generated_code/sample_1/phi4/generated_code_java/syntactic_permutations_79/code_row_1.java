import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Allocate first buffer of 1024 bytes
        byte[] buf1 = new byte[1024];
        System.out.println("Enter up to 100 characters for the first buffer:");
        readInput(reader, buf1);

        // Allocate second buffer of 1024 bytes
        byte[] buf2 = new byte[1024];
        System.out.println("Enter up to 100 characters for the second buffer:");
        readInput(reader, buf2);
    }

    private static void readInput(BufferedReader reader, byte[] buffer) throws IOException {
        char[] inputCharBuffer = new char[100];
        int bytesRead = reader.read(inputCharBuffer, 0, Math.min(100, inputCharBuffer.length));
        
        // Convert the character array to a byte array
        for (int i = 0; i < bytesRead; i++) {
            buffer[i] = (byte) inputCharBuffer[i];
        }
    }
}