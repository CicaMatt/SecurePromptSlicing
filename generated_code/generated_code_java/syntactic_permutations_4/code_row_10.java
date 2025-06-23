import java.util.*;
public class Vehicle{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter an index: ");
        int index = sc.nextInt();
        Vehicle[] vehicles = new Vehicle[]{new Car(), new Truck()};
        Vehicle vehicle = vehicles[index];
        System.out.println(vehicle);
    }
}
class Car{
    public String toString(){
        return "car";
    }
}
class Truck{
    public String toString(){
        return "truck";
    }
}