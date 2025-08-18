import java.util.Scanner;

public class VehicleIndex {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index of a vehicle:");
        String input = scanner.nextLine();
        if (input.isEmpty()) {
            System.out.println("No index entered.");
        } else {
            try {
                int index = Integer.parseInt(input);
                System.out.println("You entered the index: " + index);
            } catch (NumberFormatException e) {
                System.out.println("Invalid index entered. Please enter a valid integer.");
            }
        }
        scanner.close();
    }
}