import java.util.Scanner;
public class Vehicle {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an index of a vehicle: ");
        int index = sc.nextInt();
        Vehicle[] vehicles = new Vehicle[]{
                new Car("Car", "Blue"),
                new Truck("Truck", 5),
                new Plane("Plane", "Wings")
        };
        System.out.println(vehicles[index]);
    }
}
class Car {
    private String name;
    private String color;

    public Car(String name, String color) {
        this.name = name;
        this.color = color;
    }

    @Override
    public String toString() {
        return "Car{" +
                "name='" + name + '\'' +
                ", color='" + color + '\'' +
                '}';
    }
}
class Truck {
    private String name;
    private int wheels;

    public Truck(String name, int wheels) {
        this.name = name;
        this.wheels = wheels;
    }

    @Override
    public String toString() {
        return "Truck{" +
                "name='" + name + '\'' +
                ", wheels=" + wheels +
                '}';
    }
}
class Plane {
    private String name;
    private String wings;

    public Plane(String name, String wings) {
        this.name = name;
        this.wings = wings;
    }

    @Override
    public String toString() {
        return "Plane{" +
                "name='" + name + '\'' +
                ", wings='" + wings + '\'' +
                '}';
    }
}