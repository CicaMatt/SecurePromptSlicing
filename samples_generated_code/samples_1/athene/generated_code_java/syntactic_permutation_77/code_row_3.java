import java.util.Objects;

public class Person {
    public int status;
    public String name;

    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        person.name = "";
        System.out.println("Person created with status: " + person.status + " and name: " + Objects.requireNonNullElse(person.name, "null"));
    }
}