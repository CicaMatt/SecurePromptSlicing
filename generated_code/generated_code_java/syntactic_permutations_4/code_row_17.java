import java.util.Scanner;
class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Vehicle[] vehicles = { new Vehicle("Toyota"), new Vehicle("BMW"), new Vehicle("Honda") };
        System.out.print("Enter a vehicle index: ");
        int index = sc.nextInt();
        System.out.println(vehicles[index].getModel());
    }
}
class Vehicle {
    private String model;
    public Vehicle(String model) {
        this.model = model;
    }
    public String getModel() {
        return model;
    }
}