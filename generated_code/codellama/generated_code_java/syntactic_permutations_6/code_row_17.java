import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Truck", "Motorcycle"};
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a vehicle:");
        String userInput = scanner.nextLine();
        if (Arrays.asList(vehicles).contains(userInput)){
            System.out.println(userInput);
        } else {
            System.out.println("We do not have that vehicle.");
        }
    for (String vehicle: vehicles) {
        System.out.println(vehicle);
    }
  }
}