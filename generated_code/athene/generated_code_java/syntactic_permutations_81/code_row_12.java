import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferReaderExample {
    private static final int BUFFER_SIZE = 1024;
    private byte[] buffer = new byte[BUFFER_SIZE];
    
    public void readIntoBuffer() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String input = reader.readLine();
        if (input != null && input.length() <= BUFFER_SIZE) {
            for (int i = 0; i < input.length(); i++) {
                buffer[i] = (byte) input.charAt(i);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferReaderExample example = new BufferReaderExample();
        example.readIntoBuffer();
    }
}