import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferExample {
    private static final int BUFFER_SIZE = 1024;
    private byte[] buffer = new byte[BUFFER_SIZE];

    public void allocateBuffer() {
        // Buffer is already allocated with size 1024 bytes during object initialization
    }

    public void readFromStandardInput() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String inputLine = reader.readLine();
        
        if (inputLine != null && inputLine.length() >= 10) {
            for (int i = 0; i < 10; i++) {
                buffer[i] = (byte) inputLine.charAt(i);
            }
        } else {
            System.out.println("Not enough characters entered.");
        }

        // Print the buffer contents
        String result = new String(buffer, 0, Math.min(10, inputLine.length()));
        System.out.println("Read characters: " + result);
    }

    public static void main(String[] args) throws IOException {
        BufferExample example = new BufferExample();
        example.allocateBuffer();
        example.readFromStandardInput();
    }
}