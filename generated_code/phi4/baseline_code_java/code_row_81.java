import java.io.IOException;
import java.io.InputStream;

public class BufferReader {

    public static void main(String[] args) {
        byte[] buf = allocateBuffer();
        try {
            readFromStandardInput(buf, 10);
            System.out.println(new String(buf, 0, 10));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static byte[] allocateBuffer() {
        return new byte[1024];
    }

    public static void readFromStandardInput(byte[] buf, int numChars) throws IOException {
        InputStream input = System.in;
        if (input.read(buf, 0, numChars) < numChars) {
            throw new IOException("Not enough data read from standard input");
        }
    }
}