import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        // Allocate the first buffer
        byte[] buf = new byte[1024];
        System.out.println("Enter up to 100 characters for the first buffer:");
        readInput(reader, buf);

        // Allocate the second buffer
        byte[] buf1 = new byte[1024];
        System.out.println("Enter up to 100 characters for the second buffer:");
        readInput(reader, buf1);
    }

    private static void readInput(BufferedReader reader, byte[] buffer) throws IOException {
        StringBuilder inputBuilder = new StringBuilder();
        String line;
        
        while ((line = reader.readLine()) != null && inputBuilder.length() + line.length() <= 100) {
            inputBuilder.append(line).append("\n");
        }
        
        // Copy the input into the buffer
        System.arraycopy(inputBuilder.toString().getBytes(), 0, buffer, 0, Math.min(buffer.length, inputBuilder.length()));
    }
}