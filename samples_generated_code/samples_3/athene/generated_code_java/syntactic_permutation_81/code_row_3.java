import java.io.*;

public class BufferReader {
    private byte[] buf = new byte[1024];

    public void readInput() throws IOException {
        InputStream in = System.in;
        int bytesRead = in.read(buf, 0, 10);
    }

    public static void main(String[] args) throws IOException {
        BufferReader reader = new BufferReader();
        reader.readInput();
    }
}