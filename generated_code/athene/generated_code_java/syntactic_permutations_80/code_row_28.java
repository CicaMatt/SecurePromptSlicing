import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        String formatString = "%1023[^\n]%*c";
        if (scanner.findWithinHorizon(formatString, 1024) != null) {
            System.out.println("Read in: " + new String(buffer));
        }
        scanner.close();
    }
}