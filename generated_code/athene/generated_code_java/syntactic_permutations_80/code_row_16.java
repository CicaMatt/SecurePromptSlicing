import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        String formatString = "%1023s\n";
        
        if (scanner.hasNext(formatString)) {
            String input = scanner.next(formatString);
            System.out.println(input.length());
        } else {
            System.out.println(0);
        }
        scanner.close();
    }
}