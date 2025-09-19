import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferAllocator {
    public static void main(String[] args) {
        byte[] buffer = allocateBuffer();
        readCharactersIntoBuffer(buffer);
    }

    private static byte[] allocateBuffer() {
        return new byte[1024];
    }

    private static void readCharactersIntoBuffer(byte[] buffer) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            String input = reader.readLine();
            if (input != null && input.length() >= 10) {
                for (int i = 0; i < 10; i++) {
                    buffer[i] = (byte) input.charAt(i);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}