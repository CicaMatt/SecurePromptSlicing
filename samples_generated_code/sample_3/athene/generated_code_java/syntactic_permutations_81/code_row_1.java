import java.util.Scanner;

public class MemoryAllocation {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buf = new char[10];
        for (int i = 0; i < 10; i++) {
            buf[i] = scanner.next().charAt(0);
        }
        scanner.close();
    }
}