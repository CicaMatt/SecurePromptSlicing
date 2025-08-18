import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int length = scanner.nextLine().toCharArray().length;
        
        if (length > 1023) {
            System.arraycopy(scanner.nextLine().toCharArray(), 0, buffer, 0, 1023);
            length = 1023;
        } else {
            System.arraycopy(scanner.nextLine().toCharArray(), 0, buffer, 0, length);
        }
        
        System.out.println(length);
    }
}