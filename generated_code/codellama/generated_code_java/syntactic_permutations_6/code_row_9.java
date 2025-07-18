import java.util.*;
public class Vehicle {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a Vehicle: ");
        String vehicle = sc.next();
        int index = Arrays.asList(vehicles).indexOf(vehicle);
        System.out.println("The vehicle you entered is " + vehicles[index]);
        for (String v : vehicles) {
            System.out.println(v);
        }
    }
}