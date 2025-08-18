import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf1 = allocateBuffer(1024);
        readFromStdin(buf1, 100);

        byte[] buf2 = allocateBuffer(1024);
        readFromStdin(buf2, 100);
    }

    private static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    private static void readFromStdin(byte[] buffer, int maxChars) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder input = new StringBuilder();
        
        String line;
        while ((line = reader.readLine()) != null && input.length() < maxChars) {
            input.append(line).append("\n");
        }

        for (int i = 0; i < Math.min(buffer.length, input.length()); i++) {
            buffer[i] = (byte) input.charAt(i);
        }
    }
}