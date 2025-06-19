import java.util.*;

public class Vehicles {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter an index of a vehicle: ");
        int i = Integer.parseInt(sc.nextLine());
        String[] vehicles = {"Car", "Truck", "Motorcycle", "Bicycle"};
        System.out.println(vehicles[i]);
    }
}