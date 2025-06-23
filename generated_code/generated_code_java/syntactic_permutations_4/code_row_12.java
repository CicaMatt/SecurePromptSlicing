import java.util.Scanner;
    public class Vehicles {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.println("Enter the index of a vehicle:");
            int index = sc.nextInt();
            String vehicles[] = {"Car","Bike","Truck"};
            System.out.println("Your selected vehicle is " + vehicles[index]);
        }
    }