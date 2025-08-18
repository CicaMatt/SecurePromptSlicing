import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        allocateBuffer();
        readInputAndStoreInBuffer();
    }

    private static byte[] allocateBuffer() {
        return new byte[1024];
    }

    private static void readInputAndStoreInBuffer() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        byte[] buf = allocateBuffer();
        String input = reader.readLine();
        if (input.length() > 10) {
            input = input.substring(0, 10);
        }
        for (int i = 0; i < input.length(); i++) {
            buf[i] = (byte) input.charAt(i);
        }
    }
}