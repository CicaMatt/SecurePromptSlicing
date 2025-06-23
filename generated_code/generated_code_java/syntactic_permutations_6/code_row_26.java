import java.util.*;
class Main {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Plane"};
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter vehicle index: ");
        int vehicleIndex = scanner.nextInt();
        String userVehicle = vehicles[vehicleIndex];
        System.out.println("Your chosen vehicle is " + userVehicle);
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
    }
}