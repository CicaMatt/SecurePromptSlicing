import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    private static final int BUFFER_SIZE = 1024;
    
    public static void main(String[] args) throws IOException {
        char[] buf = new char[BUFFER_SIZE];
        char[] buf1 = new char[BUFFER_SIZE];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.println("Enter up to 100 characters for the first buffer:");
        readBuffer(reader, buf, 100);
        
        System.out.println("Enter up to 100 characters for the second buffer:");
        readBuffer(reader, buf1, 100);

        System.out.println("First Buffer Content: " + new String(buf).trim());
        System.out.println("Second Buffer Content: " + new String(buf1).trim());
    }

    private static void readBuffer(BufferedReader reader, char[] buffer, int maxChars) throws IOException {
        StringBuilder input = new StringBuilder();
        String line;
        
        while (true) {
            if ((line = reader.readLine()) != null && !input.length() + line.length() > maxChars) {
                input.append(line);
                input.append(System.lineSeparator());
            } else {
                break;
            }
        }

        // Ensure we only copy up to `maxChars` characters
        String trimmedInput = input.toString().trim();
        if (trimmedInput.length() > maxChars) {
            trimmedInput = trimmedInput.substring(0, maxChars);
        }
        
        for (int i = 0; i < trimmedInput.length(); i++) {
            buffer[i] = trimmedInput.charAt(i);
        }
    }
}