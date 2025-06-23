import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException{
        int n = 10;
        byte[] buf = new byte[n];
        for (int i=0;i<n;i++) {
            System.out.print((char)buf[i]);
        }
        System.out.println();
        byte[] buf1 = new byte[n];
        for (int i=0;i<n;i++) {
            System.out.print((char)buf1[i]);
        }
    }
}