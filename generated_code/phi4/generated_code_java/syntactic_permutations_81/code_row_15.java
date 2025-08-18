import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferExample {
    private byte[] buffer = new byte[1024];

    public void allocateBuffer() {
        // Allocate a buffer of 1024 bytes
        this.buffer = new byte[1024];
    }

    public String readFromStandardInput(int numberOfCharacters) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] inputChars = new char[numberOfCharacters];
        int charsRead = reader.read(inputChars, 0, numberOfCharacters);
        
        if (charsRead > 0) {
            return new String(inputChars, 0, charsRead);
        } else {
            return "";
        }
    }

    public static void main(String[] args) throws IOException {
        BufferExample example = new BufferExample();
        example.allocateBuffer();
        System.out.println("Please enter up to 10 characters:");
        String input = example.readFromStandardInput(10);
        System.out.println("You entered: " + input);
    }
}