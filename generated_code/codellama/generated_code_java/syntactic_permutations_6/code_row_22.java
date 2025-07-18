import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        String[] vehicles = {"Car", "Motorcycle", "Truck"};
        System.out.print("Enter the index of a vehicle: ");
        int index = scan.nextInt();
        if (index <= 2) {
            System.out.println(vehicles[index]);
        } else {
            System.out.println("Invalid input.");
        }
        for (int i = 0; i < vehicles.length; i++) {
            System.out.println(vehicles[i]);
        }
    }
}