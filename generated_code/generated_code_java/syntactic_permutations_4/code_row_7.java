import java.util.Scanner;

    public class VehicleIndex {
    	public static void main(String[] args) {
    		// Declare, instantiate and initialize an array of vehicles
    		Vehicle[] vehicles = new Vehicle[5];
    		vehicles[0] = new Car("Toyota", "Corolla", 2017);
    		vehicles[1] = new Truck("Ford", "F-150", 2018, 7500.00);
    		vehicles[2] = new Motorcycle("Harley-Davidson", "LiveWire", 2020);
    		vehicles[3] = new Car("Tesla", "Model S", 2019);
    		vehicles[4] = new Truck("Volvo", "V70", 2020, 9500.00);
    //Prompt user to enter an index
    Scanner input = new Scanner(System.in);
    System.out.print("Enter an index: ");
    int index = Integer.parseInt(input.nextLine());
    //Access and print vehicle at entered index
    Vehicle vehicle = vehicles[index];
    System.out.println(vehicle.toString());
        }
    }

    public class Vehicle {
    	private String make;
    	private String model;

    	public Vehicle() {
    	}

    	public Vehicle(String make, String model) {
    		this.make = make;
    		this.model = model;
    	}

    	public String getMake() {
    		return this.make;
    	}

    	public void setMake(String make) {
    		this.make = make;
    	}

    	public String getModel() {
    		return this.model;
    	}

    	public void setModel(String model) {
    		this.model = model;
    	}

    	@Override
    	public String toString() {
    		return "Vehicle{" +
    		"make='" + make + '\'' +
    		", model='" + model + '\'' +
    		'}';
    }
}

class Car extends Vehicle {
	private int year;

	public Car() {
	}

	public Car(String make, String model, int year) {
		super(make, model);
		this.year = year;
	}

	public int getYear() {
		return this.year;
	}

	public void setYear(int year) {
		this.year = year;
	}

	@Override
	public String toString() {
		return "Car{" +
    		"make='" + getMake() + '\'' +
    		", model='" + getModel() + '\'' +
    		", year=" + year +
    '}';
  }
}

class Truck extends Vehicle {
	private int weightCapacity;
	private double price;

	public Truck() {
	}

	public Truck(String make, String model, int weightCapacity, double price) {
		super(make, model);
		this.weightCapacity = weightCapacity;
		this.price = price;
	}

	public int getWeightCapacity() {
		return this.weightCapacity;
	}

	public void setWeightCapacity(int weightCapacity) {
		this.weightCapacity = weightCapacity;
	}

	public double getPrice() {
		return this.price;
	}

	public void setPrice(double price) {
		this.price = price;
	}

	@Override
	public String toString() {
		return "Truck{" +
    	"make='" + getMake() + '\'' +
    	", model='" + getModel() + '\'' +
    	", weightCapacity=" + weightCapacity +
    ", price=" + price +
  '}';
}

class Motorcycle extends Vehicle {
	private int year;

	public Motorcycle() {
	}

	public Motorcycle(String make, String model, int year) {
		super(make, model);
		this.year = year;
	}

	public int getYear() {
		return this.year;
	}

	public void setYear(int year) {
		this.year = year;
	}

	@Override
	public String toString() {
		return "Motorcycle{" +
    	"make='" + getMake() + '\'' +
    	", model='" + getModel() + '\'' +
    	", year=" + year +
  '}';
}