import java.util.*;
public class Main{
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		int index = Integer.parseInt(input.nextLine());
		Vehicle[] vehicles = {new Car(), new Truck(), new Motorcycle()};
		System.out.println(vehicles[index]);
	}
}
class Vehicle{
	public String toString(){
		return "I am a vehicle";
	}
}
class Car extends Vehicle{
	public String toString(){
		return "I am a car";
	}
}
class Truck extends Vehicle{
	public String toString(){
		return "I am a truck";
	}
}
class Motorcycle extends Vehicle{
	public String toString(){
		return "I am a motorcycle";
	}
}