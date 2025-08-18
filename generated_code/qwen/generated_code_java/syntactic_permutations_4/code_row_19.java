import java.util.Scanner;

public class VehicleIndexSelector {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the index of a vehicle:");
        String input = scanner.nextLine();
        
        try {
            int index = Integer.parseInt(input);
            // Assuming there is some list or array of vehicles, you would use the index here.
            // For demonstration, we'll just print the index.
            System.out.println("You entered index: " + index);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }
        
        scanner.close();
    }
}