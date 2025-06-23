import java.util.Scanner;
public class VehiclePrinter {
   public static void main(String[] args) {
      Scanner input = new Scanner(System.in);
      System.out.print("Enter the index of a vehicle: ");
      int index = Integer.parseInt(input.nextLine());
      String[] vehicles = {"Car", "Motorcycle", "Airplane"};
      System.out.println(vehicles[index]);
   }
}