import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferExample {
    public static void main(String[] args) {
        byte[] buffer = allocateBuffer(1024);
        readInputToBuffer(buffer, 10);
    }

    public static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    public static void readInputToBuffer(byte[] buffer, int length) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            String input = reader.readLine();
            if (input != null && input.length() >= length) {
                for (int i = 0; i < length; i++) {
                    buffer[i] = (byte) input.charAt(i);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                reader.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}