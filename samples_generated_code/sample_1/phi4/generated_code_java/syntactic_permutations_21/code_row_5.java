import java.util.Scanner;

public class AddToInput {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        if (args.length != 1 || !args[0].matches("\\d+")) {
            System.out.println("Please provide a single integer argument.");
            return;
        }
        
        int inputValue = Integer.parseInt(args[0]);
        System.out.print("Enter a number to add: ");
        int numberToAdd = scanner.nextInt();
        
        int result = inputValue + numberToAdd;
        System.out.println("The result is: " + result);
    }
}