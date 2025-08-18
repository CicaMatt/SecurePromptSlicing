import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferManager {

    private static final int BUFFER_SIZE = 1024;
    private byte[] buffer;

    public void allocateBuffer() {
        buffer = new byte[BUFFER_SIZE];
    }

    public void readFromStandardIn() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String line;
        int offset = 0;

        while ((line = reader.readLine()) != null && offset < BUFFER_SIZE) {
            byte[] bytes = line.getBytes();
            if (offset + bytes.length > BUFFER_SIZE) {
                break;
            }
            System.arraycopy(bytes, 0, buffer, offset, bytes.length);
            offset += bytes.length;
        }

        // Close the BufferedReader
        reader.close();
    }

    public static void main(String[] args) {
        BufferManager manager = new BufferManager();

        manager.allocateBuffer();
        
        try {
            manager.readFromStandardIn();
        } catch (IOException e) {
            System.err.println("An error occurred while reading from standard input.");
        }
    }
}