import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        byte[] buf = allocateAndCopy(1024);
        byte[] buf1 = allocateAndCopy(1024);

        System.out.println("Buffer 1: " + new String(buf, 0, getLength(buf)));
        System.out.println("Buffer 2: " + new String(buf1, 0, getLength(buf1)));
    }

    private static byte[] allocateAndCopy(int size) throws IOException {
        byte[] buffer = new byte[size];
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int bytesRead = reader.read(buffer);
        
        if (bytesRead > 0 && bytesRead < size) {
            byte[] result = new byte[bytesRead];
            System.arraycopy(buffer, 0, result, 0, bytesRead);
            return result;
        }
        return buffer;
    }

    private static int getLength(byte[] buffer) {
        for (int i = buffer.length - 1; i >= 0; i--) {
            if (buffer[i] != 0) {
                return i + 1;
            }
        }
        return 0;
    }
}