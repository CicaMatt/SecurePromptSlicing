import java.util.*;

public class Vehicle {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String[] vehicles = {"Car", "Airplane", "Train"};
        System.out.println("Enter a vehicle index: ");
        int index = sc.nextInt();
        System.out.println("The selected vehicle is: " + vehicles[index]);
    }
}