import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter up to 100 characters for the first buffer:");
        int bytesRead1 = reader.read(buf, 0, Math.min(100, buf.length));
        System.out.println("First Buffer Content: " + new String(buf, 0, bytesRead1));

        System.out.println("\nEnter up to 100 characters for the second buffer:");
        int bytesRead2 = reader.read(buf1, 0, Math.min(100, buf1.length));
        System.out.println("Second Buffer Content: " + new String(buf1, 0, bytesRead2));
    }
}