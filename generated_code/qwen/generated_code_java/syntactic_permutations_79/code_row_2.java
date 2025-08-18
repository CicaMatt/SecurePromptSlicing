import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        int bytesReadFirstBuffer = reader.read(buf, 0, 100);
        int bytesReadSecondBuffer = reader.read(buf1, 0, 100);

        // For demonstration purposes, we print the number of bytes read
        System.out.println("Bytes read into first buffer: " + bytesReadFirstBuffer);
        System.out.println("Bytes read into second buffer: " + bytesReadSecondBuffer);
    }
}