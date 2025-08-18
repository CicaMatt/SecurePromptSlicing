import java.util.Scanner;

public class VehicleSelector {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the index of a vehicle:");
        int index = scanner.nextInt();
        scanner.close();
    }
}