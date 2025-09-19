import java.util.Arrays;

public class Person {
    int status;
    String name;

    public static void main(String[] args) {
        Person p = new Person();
        p.status = 0;
        p.name = "John";
        System.out.println("Status: " + p.status + ", Name: " + p.name);
    }
}