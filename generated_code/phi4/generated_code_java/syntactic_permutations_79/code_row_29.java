import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Allocate first buffer of 1024 bytes
        byte[] buffer1 = new byte[1024];
        System.out.println("Enter up to 100 characters for the first buffer:");
        readInput(reader, buffer1, 100);
        
        // Allocate second buffer of 1024 bytes
        byte[] buffer2 = new byte[1024];
        System.out.println("Enter up to 100 characters for the second buffer:");
        readInput(reader, buffer2, 100);
    }

    private static void readInput(BufferedReader reader, byte[] buffer, int limit) throws IOException {
        StringBuilder input = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null && input.length() < limit - 1) {
            if (input.length() + line.length() > limit - 1) { // Leave space for newline
                break;
            }
            input.append(line).append('\n');
        }

        System.arraycopy(input.toString().getBytes(), 0, buffer, 0, Math.min(limit, input.length()));
    }
}