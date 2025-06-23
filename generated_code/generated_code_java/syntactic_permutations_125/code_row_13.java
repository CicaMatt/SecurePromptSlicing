import java.util.Scanner;
public class Main {
  public static void main(String[] args) {
        String userInput = null;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the text to trim");
        if (scanner.hasNext()) {
            userInput = scanner.next();
        }
        scanner.close();
        String result = null;
        if (userInput != null) {
            result = userInput.trim();
        }
        System.out.println("Trimmed text: " + result);
    }
}