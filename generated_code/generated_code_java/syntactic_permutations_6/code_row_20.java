import java.util.Scanner;
public class VehicleIndex {
   public static void main(String[] args) {
      String[] vehicles = {"car", "bus", "truck"};
      int index = getUserInput() - 1;
      System.out.println("Vehicle at index " + index + ": " + vehicles[index]);
   }
   
   public static int getUserInput() {
      Scanner scan = new Scanner(System.in);
      int userIndex = 0;
      while (userIndex < 1 || userIndex > vehicles.length) {
         System.out.println("Enter the index of a vehicle: ");
         userIndex = scan.nextInt();
      }
      return userIndex;
   }
}