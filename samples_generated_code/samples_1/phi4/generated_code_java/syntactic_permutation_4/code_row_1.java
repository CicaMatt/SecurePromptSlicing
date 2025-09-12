import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};

        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter an index of a vehicle:");
        int index;
        try {
            index = Integer.parseInt(scanner.nextLine());
            
            if (index >= 0 && index < vehicles.length) {
                System.out.println("Vehicle at the entered index: " + vehicles[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }

        scanner.close();
    }
}