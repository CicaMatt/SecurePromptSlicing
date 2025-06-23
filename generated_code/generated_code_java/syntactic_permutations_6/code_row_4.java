import java.util.Scanner;
    public class Vehicles {
        public static void main(String[] args) {
            String[] vehicles = {"Car","Truck","Motorcycle","Bicycle"};
            Scanner input = new Scanner(System.in);
            System.out.println("Enter the index of your vehicle:");
            int user_vehicle = input.nextInt();
            System.out.println("Your vehicle is " + vehicles[user_vehicle]);
            for (String v: vehicles) {
                System.out.println(v);
            }
        }
    }