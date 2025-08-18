import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter up to 1024 characters for buffer 1:");
        readInput(buf, reader);

        System.out.println("Enter up to 1024 characters for buffer 2:");
        readInput(buf1, reader);

        // Output the contents of buf and buf1 to verify
        System.out.println("Buffer 1 content: " + new String(buf));
        System.out.println("Buffer 2 content: " + new String(buf1));
    }

    private static void readInput(byte[] buffer, BufferedReader reader) throws IOException {
        int length = reader.read(buffer);
        if (length > 0) {
            // Ensure the string is null-terminated by setting the last byte to 0
            if (length < buffer.length) {
                buffer[length] = '\0';
            }
        }
    }
}