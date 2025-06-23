import java.util.*;
public class Vehicles{
	String[] vehicles = new String[3];
	Scanner sc = new Scanner(System.in);
	public static void main(String args[]){
		vehicles[0] = "Car";
		vehicles[1] = "Bike";
		vehicles[2] = "Truck";
		System.out.println("Enter the index of your preferred vehicle: ");
		String choice = sc.nextLine();
		int indexOfChoice = Integer.parseInt(choice);
		System.out.println("Your preferred vehicle is: " + vehicles[indexOfChoice]);
	}
}