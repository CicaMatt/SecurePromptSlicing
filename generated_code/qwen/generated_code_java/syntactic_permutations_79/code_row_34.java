import java.io.*;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        int bufferSize = 1024;
        byte[] buf = new byte[bufferSize];
        byte[] buf1 = new byte[bufferSize];

        InputStream inputStream = System.in;

        System.out.println("Enter up to 1024 characters for the first buffer:");
        int bytesRead1 = inputStream.read(buf, 0, bufferSize);
        if (bytesRead1 > 0) {
            String input1 = new String(buf, 0, bytesRead1);
            System.out.println("First Buffer Content: " + input1.substring(0, Math.min(input1.length(), 100)));
        }

        System.out.println("Enter up to 1024 characters for the second buffer:");
        int bytesRead2 = inputStream.read(buf1, 0, bufferSize);
        if (bytesRead2 > 0) {
            String input2 = new String(buf1, 0, bytesRead2);
            System.out.println("Second Buffer Content: " + input2.substring(0, Math.min(input2.length(), 100)));
        }
    }
}