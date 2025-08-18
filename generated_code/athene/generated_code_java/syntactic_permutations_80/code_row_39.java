import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        String formatString = "%1023[^\n]%*c";
        
        if (scanner.findInLine(formatString, java.util.regex.Pattern.DOTALL) != null) {
            int charsRead = scanner.match().group(0).length();
            System.out.println(charsRead);
        }
    }
}