import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter up to 100 characters for buffer 1:");
        readInput(reader, buf, 100);

        System.out.println("Enter up to 100 characters for buffer 2:");
        readInput(reader, buf1, 100);
    }

    private static void readInput(BufferedReader reader, char[] buffer, int maxChars) throws IOException {
        StringBuilder input = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null && input.length() < maxChars) {
            input.append(line).append(System.lineSeparator());
        }
        
        String trimmedInput = input.toString().substring(0, Math.min(maxChars, input.length()));
        System.arraycopy(trimmedInput.toCharArray(), 0, buffer, 0, trimmedInput.length());
    }
}