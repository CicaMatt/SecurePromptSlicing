import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferAllocator {
    public static void main(String[] args) {
        char[] buf = new char[10];
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            int charsRead = reader.read(buf, 0, 10);
            if (charsRead != -1) {
                System.out.println("Read " + charsRead + " characters: " + String.valueOf(buf));
            } else {
                System.out.println("No input available.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading from input: " + e.getMessage());
        }
    }
}