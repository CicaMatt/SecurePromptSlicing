import java.util.Scanner;

public class CommandLineReader {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter a value:");
        String input = scanner.nextLine();
        
        System.out.println("You entered: " + input);
        
        scanner.close();
        
        // Explicitly returning 0, although not necessary in a main method
        int result = 0;
    }
}