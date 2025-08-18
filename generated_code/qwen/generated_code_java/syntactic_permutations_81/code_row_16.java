import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferExample {
    public static void main(String[] args) {
        byte[] buffer = allocateBuffer(1024);
        readInput(buffer, 10);
        System.out.println(new String(buffer).trim());
    }

    public static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    public static void readInput(byte[] buf, int length) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            reader.read(buf, 0, length);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}