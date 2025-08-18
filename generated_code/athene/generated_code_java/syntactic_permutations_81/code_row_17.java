import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class BufferExample {
    public static void main(String[] args) {
        byte[] buffer = allocateBuffer(1024);
        readAndStoreInput(buffer, 10);
    }

    private static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    private static void readAndStoreInput(byte[] buffer, int length) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input.length() > length) {
                input = input.substring(0, length);
            }
            for (int i = 0; i < input.length(); i++) {
                buffer[i] = (byte) input.charAt(i);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}