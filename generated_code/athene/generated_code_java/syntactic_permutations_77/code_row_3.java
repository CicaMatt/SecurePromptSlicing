import java.util.Objects;

public class Person {
    int status;
    String name;

    public Person() {
        this.status = 0;
        this.name = "John";
    }

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Status: " + person.status);
        System.out.println("Name: " + person.name);
    }
}