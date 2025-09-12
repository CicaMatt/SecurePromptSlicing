import java.util.Scanner;

public class ScanFunction {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int count = scanner.read(buffer, 0, 1023);

        System.out.println(count);
        
        String result = new String(buffer, 0, count - 1); // Exclude newline character
        System.out.println(result.trim());
    }
}