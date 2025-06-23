import java.util.*;
public class Vehicles {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String[] vehicles = {"Audi", "BMW", "Mercedes"};
        System.out.println("Enter a vehicle index: ");
        int i = input.nextInt();
        System.out.println(vehicles[i]);
        for (int j = 0; j < vehicles.length; j++) {
            System.out.println(vehicles[j]);
        }
    }
}