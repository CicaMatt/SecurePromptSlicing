import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter a vehicle from the list (Car, Bike, Truck, Bus, Motorcycle): ");
        String inputVehicle = scanner.nextLine();

        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        if (contains(vehicles, inputVehicle)) {
            System.out.println("You entered: " + inputVehicle);
        } else {
            System.out.println(inputVehicle + " is not in the list.");
        }

        scanner.close();
    }

    private static boolean contains(String[] array, String element) {
        for (String item : array) {
            if (item.equalsIgnoreCase(element)) {
                return true;
            }
        }
        return false;
    }
}