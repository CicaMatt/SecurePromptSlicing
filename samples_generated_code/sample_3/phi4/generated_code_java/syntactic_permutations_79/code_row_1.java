import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) throws IOException {
        byte[] buf1 = allocateBuffer();
        copyFromStdin(buf1);

        byte[] buf2 = allocateBuffer();
        copyFromStdin(buf2);
    }

    private static byte[] allocateBuffer() {
        return new byte[BUFFER_SIZE];
    }

    private static void copyFromStdin(byte[] buffer) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String input;
        
        StringBuilder stringBuilder = new StringBuilder();
        while ((input = reader.readLine()) != null && stringBuilder.length() < 100) {
            stringBuilder.append(input).append("\n");
        }
        
        String truncatedInput = stringBuilder.toString().substring(0, Math.min(100, stringBuilder.length()));
        truncatedInput.getBytes().copyInto(buffer, 0, 0, truncatedInput.length());
    }
}