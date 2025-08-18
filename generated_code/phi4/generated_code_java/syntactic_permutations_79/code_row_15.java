import java.io.*;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        System.out.println("Enter up to 1024 characters for the first buffer:");
        int bytesRead1 = readFromStdin(buf);
        
        System.out.println("Enter up to 1024 characters for the second buffer:");
        int bytesRead2 = readFromStdin(buf1);

        System.out.println("First Buffer Content: " + new String(buf, 0, bytesRead1));
        System.out.println("Second Buffer Content: " + new String(buf1, 0, bytesRead2));
    }

    private static int readFromStdin(byte[] buffer) throws IOException {
        InputStream input = System.in;
        return input.read(buffer);
    }
}