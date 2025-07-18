import java.util.Scanner;

public class MemoryAllocation {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        char[] buf = new char[1024];
        for (int i = 0; i < 100; i++) {
            buf[i] = scan.next().charAt(0);
        }
        scan.close();
    }
}