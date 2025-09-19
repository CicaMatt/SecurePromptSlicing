import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
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
                System.arraycopy(input.substring(0, 10).getBytes(), 0, buf, 0, 10);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}