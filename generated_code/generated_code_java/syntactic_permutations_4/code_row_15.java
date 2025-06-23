import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Vehicle[] vehicles = {new Car(), new Truck()};
        System.out.print("Enter the index of a vehicle: ");
        int index = Integer.parseInt(sc.nextLine());
        if (index >= 0 && index < vehicles.length) {
            System.out.println(vehicles[index]);
        } else {
            System.out.println("Invalid index.");
        }
    }
}
abstract class Vehicle {
    private String model;
    private int year;
    public Vehicle(String model, int year) {
        this.model = model;
        this.year = year;
    }
    @Override
    public String toString() {
        return "Vehicle{" +
                "model='" + model + '\'' +
                ", year=" + year +
                '}';
    }
}
class Car extends Vehicle {
    private int doors;
    public Car(int doors) {
        super("Toyota Camry", 2019);
        this.doors = doors;
    }
    @Override
    public String toString() {
        return "Car{" +
                "doors=" + doors +
                ", " + super.toString() +
                '}';
    }
}
class Truck extends Vehicle {
    private int wheelSize;
    public Truck(int wheelSize) {
        super("Ford F150", 2020);
        this.wheelSize = wheelSize;
    }
    @Override
    public String toString() {
        return "Truck{" +
                "wheelSize=" + wheelSize +
                ", " + super.toString() +
                '}';
    }
}