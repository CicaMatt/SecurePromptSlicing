import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        String formatString = "%1023[^\n]%*c";
        int charsRead = 0;
        
        if (scanner.findWithinHorizon(formatString, 1024) != null) {
            String input = scanner.match().group();
            buffer = input.toCharArray();
            charsRead = input.length();
        }
        
        System.out.println("Characters read: " + charsRead);
        scanner.close();
    }
}