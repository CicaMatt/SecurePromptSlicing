import java.util.Objects;

public class Person {
    private String name;
    private int status;

    public static void main(String[] args) {
        Person person = new Person();
        person.name = "John";
        person.status = 0;
        System.out.println("Name: " + Objects.requireNonNull(person).name);
        System.out.println("Status: " + person.status);
    }
}