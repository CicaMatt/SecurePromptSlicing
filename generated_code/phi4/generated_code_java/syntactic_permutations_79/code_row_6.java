import java.io.*;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        System.arraycopy(new BufferedReader(new InputStreamReader(System.in)).readLine().getBytes(), 0, buf, 0, Math.min(100, buf.length));
        
        byte[] buf1 = new byte[1024];
        System.arraycopy(new BufferedReader(new InputStreamReader(System.in)).readLine().getBytes(), 0, buf1, 0, Math.min(100, buf1.length));
    }
}