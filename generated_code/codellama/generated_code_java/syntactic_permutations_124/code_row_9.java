import java.util.Scanner;

public class Hello {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        if (sc.hasNext()) {
            String input = sc.next();
            System.out.println("The argument is: " + input);
            String trimmedInput = input.trim();
            System.out.println("Trimmed the argument to: " + trimmedInput);
        } else {
            System.err.println("No arguments");
        }
    }
}