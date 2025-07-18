import java.util.Scanner;
public class JavaVehicle {
  public static void main(String[] args) {
    Scanner sc = new Scanner (System.in);
    int i = sc.nextInt();
    String[] vehicles = {"Car", "Motorbike", "Truck"};
    System.out.println("The vehicle is: " + vehicles[i]);
  }
}