import java.io.IOException;

public class BufferExample {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        readTenCharacters(buf);
    }

    public static void readTenCharacters(byte[] buffer) {
        try {
            System.in.read(buffer, 0, 10);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}