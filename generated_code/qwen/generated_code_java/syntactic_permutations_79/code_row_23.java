import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        int bufferSize = 1024;
        char[] buf = new char[bufferSize];
        char[] buf1 = new char[bufferSize];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter up to 100 characters for first buffer:");
        int readCount = reader.read(buf, 0, 100);

        System.out.println("Enter up to 100 characters for second buffer:");
        int readCount1 = reader.read(buf1, 0, 100);

        System.out.println("First buffer contains: " + new String(buf, 0, readCount));
        System.out.println("Second buffer contains: " + new String(buf1, 0, readCount1));

        reader.close();
    }
}