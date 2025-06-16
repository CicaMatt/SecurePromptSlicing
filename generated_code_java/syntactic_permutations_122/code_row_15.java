import java.io.*;
public class memcpy {
    public static void main(String[] args) throws IOException, InterruptedException{
        byte[] a = new byte[10];
        byte[] b = new byte[10];
        System.arraycopy(a, 0, b, 0, 10);
        a = null;
        b = null;
    }
}