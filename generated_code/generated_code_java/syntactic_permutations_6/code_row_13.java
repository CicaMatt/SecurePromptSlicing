import java.util.ArrayList;
import java.util.Scanner;
class Main {
  public static void main(String[] args) {
    ArrayList<String> vehicles = new ArrayList<String>();
    vehicles.add("Car");
    vehicles.add("Motorcycle");
    vehicles.add("Airplane");
    vehicles.add("Boat");
  	Scanner sc = new Scanner(System.in);
    System.out.print("Enter the index of a vehicle: ");
    int input = sc.nextInt();
    String selectedVehicle = vehicles.get(input - 1);
    System.out.println(selectedVehicle);
    for (String vehicle : vehicles) {
      System.out.println(vehicle);
    }
  }
}