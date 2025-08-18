import java.io.IOException;
import java.nio.ByteBuffer;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        ByteBuffer buffer = allocateBuffer(1024);
        
        char[] buf = new char[10];
        readFromStandardInput(buf);

        for (char c : buf) {
            System.out.print(c);
        }
    }

    private static ByteBuffer allocateBuffer(int size) {
        return ByteBuffer.allocate(size);
    }

    private static void readFromStandardInput(char[] buf) throws IOException {
        java.io.BufferedReader reader = new java.io.BufferedReader(new java.io.InputStreamReader(System.in));
        String input = reader.readLine();
        
        if (input != null && input.length() >= 10) {
            for (int i = 0; i < 10; i++) {
                buf[i] = input.charAt(i);
            }
        } else {
            System.arraycopy(input == null ? new char[10] : input.toCharArray(), 0, buf, 0, Math.min(10, input != null ? input.length() : 0));
        }
    }
}