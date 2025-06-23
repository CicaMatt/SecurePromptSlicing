import java.util.Scanner;
	public class Vehicles {
	  public static void main(String[] args) {
	   String[] vehicles = {"Car","Truck", "Motorcycle"};
     Scanner sc=new Scanner (System.in);
		int index =sc.nextInt();
		System.out.println("Vehicle at index "+index+": "+vehicles[index]);
        for(String vehicle: vehicles){
            System.out.println(vehicle);
       } 
	}
    }