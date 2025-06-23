import java.util.*;
    public class Vehicles {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            int num;
            String[] vehicles = {"car", "plane", "boat"};
            
            System.out.println("Please enter an index of a vehicle");
            num = sc.nextInt();
            int index = Integer.parseInt(String.valueOf(num));
            System.out.println(vehicles[index]);
        }
    }