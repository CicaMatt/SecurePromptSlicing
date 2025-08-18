import java.util.Scanner;

public class VehicleIndex {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the index of a vehicle: ");
        String input = scanner.nextLine();
        
        try {
            int index = Integer.parseInt(input);
            // You can now use the integer 'index' for further processing
            System.out.println("The entered index is: " + index);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }
        
        scanner.close();
    }
}