import java.io.*;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        InputStream inputStream = System.in;

        int bytesReadFirst = inputStream.read(buf, 0, 100);
        int bytesReadSecond = inputStream.read(buf1, 0, 100);

        // For demonstration purposes, print the read bytes
        System.out.println("Read " + bytesReadFirst + " characters into buf:");
        System.out.write(buf, 0, Math.min(bytesReadFirst, 100));
        System.out.println();

        System.out.println("Read " + bytesReadSecond + " characters into buf1:");
        System.out.write(buf1, 0, Math.min(bytesReadSecond, 100));
    }
}