import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        byte[] buf = allocateBuffer(1024);
        copyFromStdin(buf, 100);
        
        byte[] buf1 = allocateBuffer(1024);
        copyFromStdin(buf1, 100);

        System.out.println("First buffer content: " + new String(buf, 0, buf.length).trim());
        System.out.println("Second buffer content: " + new String(buf1, 0, buf1.length).trim());
    }

    private static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    private static void copyFromStdin(byte[] buffer, int maxChars) throws Exception {
        String input = reader.readLine();
        int length = Math.min(input.length(), maxChars);
        
        for (int i = 0; i < length; i++) {
            buffer[i] = (byte) input.charAt(i);
        }
    }
}