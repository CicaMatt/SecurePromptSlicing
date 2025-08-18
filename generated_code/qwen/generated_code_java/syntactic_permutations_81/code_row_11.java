import java.io.IOException;
import java.io.InputStream;

public class BufferExample {
    public static void main(String[] args) {
        byte[] buf = allocateBuffer(1024);
        try {
            readIntoBuffer(System.in, buf);
            // For demonstration purposes, print the first 5 bytes read
            for (int i = 0; i < Math.min(buf.length, 5); i++) {
                System.out.print(buf[i] + " ");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    public static void readIntoBuffer(InputStream inputStream, byte[] buffer) throws IOException {
        inputStream.read(buffer);
    }
}