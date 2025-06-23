import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int bufSize = 1024;
        byte[] buf = new byte[bufSize];
        sc.nextLine().getBytes(0, bufSize, buf, 0);
        
        byte[] buf1 = new byte[bufSize];
        sc.nextLine().getBytes(0, bufSize, buf1, 0);
    }
}