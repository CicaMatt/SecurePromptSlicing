import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) throws IOException {
        // Allocate first buffer and read data
        byte[] buf1 = new byte[1024];
        System.out.println("Enter up to 100 characters for the first input:");
        readInput(buf1, 100);

        // Allocate second buffer and read data
        byte[] buf2 = new byte[1024];
        System.out.println("Enter up to 100 characters for the second input:");
        readInput(buf2, 100);
    }

    private static void readInput(byte[] buffer, int maxChars) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        
        String line;
        while ((line = reader.readLine()) != null && sb.length() < maxChars) {
            sb.append(line).append('\n');
        }
        
        int lengthToCopy = Math.min(sb.length(), buffer.length);
        System.arraycopy(sb.toString().getBytes(), 0, buffer, 0, lengthToCopy);
    }
}