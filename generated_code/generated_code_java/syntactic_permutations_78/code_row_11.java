import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int size = sc.nextInt();
        Person p = new Person(size);
        System.out.println("Person: " + p.name);
        System.out.println("Status: " + p.status);
    }
}
class Person {
    String name;
    int status;

    public Person(int size) {
        this.name = "John";
        this.status = 0;
    }
}