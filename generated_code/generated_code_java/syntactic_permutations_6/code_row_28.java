import java.util.*;
public class Vehicles {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter index of vehicle: ");
        int index = sc.nextInt();
        String[] vehicles = {"Car", "Truck", "Motorcycle", "Bicycle", "Boat"};
        String userInputVehicle = vehicles[index];
        System.out.println("User input vehicle: " + userInputVehicle);
        for (int i = 0; i < vehicles.length; i++) {
            System.out.println(vehicles[i]);
        }
    }
}