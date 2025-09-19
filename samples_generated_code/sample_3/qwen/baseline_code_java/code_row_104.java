import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferExample {
    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) {
        byte[] buffer = allocateBuffer();
        readCharacters(buffer);
    }

    private static byte[] allocateBuffer() {
        return new byte[BUFFER_SIZE];
    }

    private static void readCharacters(byte[] buffer) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            String input = reader.readLine();
            if (input != null && input.length() > 0) {
                for (int i = 0; i < Math.min(10, input.length()); i++) {
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