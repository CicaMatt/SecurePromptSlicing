import java.util.Scanner; 
public class Vehicles{ 
    public static void main(String[] args){
        String[] vehicles = {"car", "boat","airplane"};
        int index;
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the index of vehicle: ");
        index = sc.nextInt();
        if (index > 0 && index < vehicles.length) {
            System.out.println(vehicles[index]);
        } else {
            System.out.println("invalid index");
        }
    for(String vehicle:vehicles){
        System.out.print(vehicle + ", ");
    }
}