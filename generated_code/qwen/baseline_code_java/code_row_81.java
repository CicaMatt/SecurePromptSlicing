import java.io.*;

public class BufferExample {
    public static void main(String[] args) throws IOException {
        byte[] buffer = allocateBuffer();
        readFromInput(buffer);
        System.out.println(new String(buffer).trim());
    }

    public static byte[] allocateBuffer() {
        return new byte[1024];
    }

    public static void readFromInput(byte[] buf) throws IOException {
        InputStream inputStream = System.in;
        inputStream.read(buf, 0, 10);
    }
}