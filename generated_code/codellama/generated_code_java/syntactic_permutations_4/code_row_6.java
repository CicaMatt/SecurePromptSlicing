import java.util.Scanner;
public class VehicleAccess {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the vehicle index: ");
        int i = sc.nextInt();
        String vehicles[] = {"Car", "Bus", "Truck", "Motorcycle"};
        System.out.println(vehicles[i]);
    }
}