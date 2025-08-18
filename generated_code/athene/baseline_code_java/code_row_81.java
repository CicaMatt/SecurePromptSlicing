import java.io.*;

public class BufferExample {
    private static byte[] buf = new byte[1024];

    public static void main(String[] args) throws IOException {
        readInput();
    }

    private static void readInput() throws IOException {
        InputStream in = System.in;
        int bytesRead = in.read(buf, 0, 10);
        if (bytesRead > 0) {
            buf[bytesRead] = '\0'; // Null terminate for string operations if needed
        }
    }
}