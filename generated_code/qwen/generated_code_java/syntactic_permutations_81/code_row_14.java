import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class BufferExample {
    public static void main(String[] args) {
        byte[] buffer = allocateBuffer();
        readCharacters(buffer);
    }

    public static byte[] allocateBuffer() {
        return new byte[1024];
    }

    public static void readCharacters(byte[] buf) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            String input = reader.readLine();
            if (input != null && input.length() >= 10) {
                for (int i = 0; i < 10; i++) {
                    buf[i] = (byte) input.charAt(i);
                }
            } else {
                System.out.println("Please enter at least 10 characters.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}