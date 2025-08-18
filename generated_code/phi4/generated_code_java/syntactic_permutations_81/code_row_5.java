import java.io.*;

public class BufferExample {
    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) throws IOException {
        byte[] buffer = new byte[BUFFER_SIZE];
        
        readAndStore(buffer);
        
        // For demonstration, print the first 10 characters as a string
        System.out.println(new String(buffer, 0, 10));
    }

    private static void readAndStore(byte[] buf) throws IOException {
        try (InputStream input = new BufferedInputStream(System.in)) {
            int bytesRead = input.read(buf, 0, 10);
            
            if (bytesRead == -1) {
                System.out.println("End of stream reached");
            }
        }
    }
}