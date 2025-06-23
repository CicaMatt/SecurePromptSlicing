import java.util.*;
public class Vehicles {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Motorcycle", "Bicycle"};
        System.out.println("Enter the index of a vehicle");
        Scanner sc = new Scanner(System.in);
        int index = sc.nextInt();
        System.out.println("Vehicle at index " + index + ": " + vehicles[index]);

        for (String v: vehicles){
            System.out.println(v);
        }
    }
}