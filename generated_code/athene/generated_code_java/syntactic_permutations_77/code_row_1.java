import java.util.Objects;

public class Person {
    private String name;
    private int status;

    public Person() {
        this.name = "John";
        this.status = 0;
    }

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Name: " + Objects.requireNonNull(person).name);
        System.out.println("Status: " + person.status);
    }
}