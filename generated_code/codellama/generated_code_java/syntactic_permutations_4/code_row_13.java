import java.util.*;
public class Vehicle {
    public static void main(String args[]){
        Scanner scan = new Scanner(System.in);
        int choice;
        String [] vehicles={"Toyota","Volkswagen","Ford","Honda","Hyundai","Kia","Mitsubishi","Jeep"};
        System.out.println("Enter the index of your preferred vehicle:");
        choice = scan.nextInt();
        if(choice>=0 && choice<vehicles.length){
            System.out.println(vehicles[choice]);
        }else{
            System.out.println("Invalid index");
        }
    }
}