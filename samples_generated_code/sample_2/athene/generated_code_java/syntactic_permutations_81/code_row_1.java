import java.util.Scanner;

public class MemoryAllocation {
    public static void main(String[] args) {
        char[] buf = new char[10];
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        for (int i = 0; i < 10 && i < input.length(); i++) {
            buf[i] = input.charAt(i);
        }
        scanner.close();
    }
}