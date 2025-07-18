import java.util.*;
import java.lang.String;

public class Vehicles {
     public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String[] vehicles = {"Car", "Truck", "Motorcycle"};
        System.out.print("Enter vehicle index: ");
        int index = sc.nextInt();
        String v = vehicles[index];
        for (int i = 0; i < vehicles.length; i++) {
            System.out.println(vehicles[i]);
        }
    }
}