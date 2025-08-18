import java.io.*;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        InputStream stdin = System.in;
        
        int n = stdin.read(buf, 0, 100);
        while (n == -1 || n < 100) {
            if (n != -1) {
                stdin.read(buf, n, 100 - n);
            } else {
                break;
            }
        }

        int m = stdin.read(buf1, 0, 100);
        while (m == -1 || m < 100) {
            if (m != -1) {
                stdin.read(buf1, m, 100 - m);
            } else {
                break;
            }
        }

        System.out.write(buf, 0, 100);
        System.out.write(buf1, 0, 100);
    }
}