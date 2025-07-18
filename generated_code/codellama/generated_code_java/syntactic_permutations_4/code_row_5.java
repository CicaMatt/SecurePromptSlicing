import java.util.*;

public class Vehicles {
    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index of a vehicle.");
        int idx = scanner.nextInt();
        String[] vehicles = {"Toyota", "Honda", "BMW"};
        System.out.println("The vehicle at the entered index is: " + vehicles[idx]);
    }
}