import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferExample {

    public static void main(String[] args) {
        byte[] buffer = allocateBuffer();
        char[] inputChars = new char[10];
        
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            System.out.println("Enter 10 characters:");
            if (reader.read(inputChars) == 10) {
                String inputString = new String(inputChars);
                System.out.println("You entered: " + inputString);
            } else {
                System.out.println("Not enough characters were entered.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading input: " + e.getMessage());
        }
    }

    public static byte[] allocateBuffer() {
        return new byte[1024];
    }
}