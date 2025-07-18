import java.util.*; 
class Vehicle { 
    int wheels; 
    String type; 
} 
public class Main { 
    public static void main(String[] args) { 
        Scanner sc = new Scanner(System.in); 
        System.out.println("Enter an index of vehicle: "); 
        int i = sc.nextInt(); 
        Vehicle vehicleArray[] = new Vehicle[5]; 
        for (int j = 0; j < vehicleArray.length; j++) { 
            vehicleArray[j] = new Vehicle(); 
            if (i == j) { 
                System.out.println("Vehicle at index " + i + " is: "); 
            } 
        } 
    } 
}