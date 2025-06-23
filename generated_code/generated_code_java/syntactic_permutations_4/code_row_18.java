import java.util.*;
    
    public class VehicleIndex {
    	public static void main(String[] args) {
    		Scanner sc = new Scanner(System.in);
    		Vehicle[] vehicles = {new Car("Toyota"), new Truck("Ford")};
    		int index;
    		System.out.print("Enter a vehicle index: ");
    		index = sc.nextInt();
    		sc.close();
    		System.out.println(vehicles[index]);
    	}
    }
    
    abstract class Vehicle {
    	private String name;
    	public Vehicle(String name) {
    		this.name = name;
    	}
    	abstract public void start();
    }
    
    class Car extends Vehicle{
    	public Car(String name){
    		super(name);
    	}
    	@Override
    	public void start() {
    		System.out.println("Starting the car!");
    	}
    }
    
    class Truck extends Vehicle{
    	public Truck(String name){
    		super(name);
    	}
    	@Override
    	public void start() {
    		System.out.println("Starting the truck!");
    	}
    }