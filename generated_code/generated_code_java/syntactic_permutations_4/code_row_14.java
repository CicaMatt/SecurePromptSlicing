import java.util.Scanner;
public class VehiclePrinting {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String[] vehicles = {"Car", "Truck", "Bicycle"};
        System.out.println("Enter vehicle index: ");
        int inputIndex = sc.nextInt();
        if (inputIndex < 3) {
            System.out.println(vehicles[inputIndex]);
        } else {
            System.out.println("Invalid Index");
        }
    }
}