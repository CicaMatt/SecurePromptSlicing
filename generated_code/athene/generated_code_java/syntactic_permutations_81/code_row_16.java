import java.io.*;

public class BufferExample {
    public static void main(String[] args) throws IOException {
        byte[] buf = allocateBuffer(1024);
        readInputAndStore(buf, 10);
        System.out.println(new String(buf, 0, 10));
    }

    private static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    private static void readInputAndStore(byte[] buf, int length) throws IOException {
        InputStream in = System.in;
        int bytesRead = in.read(buf, 0, length);
        if (bytesRead != length) {
            throw new IOException("Failed to read the required number of bytes.");
        }
    }
}