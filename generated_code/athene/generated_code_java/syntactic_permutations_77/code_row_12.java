import java.util.Objects;

public class Person {
    private String name;
    private int status;

    public static void main(String[] args) {
        Person person = new Person();
        person.setName("John");
        person.setStatus(0);
        System.out.println(person);
    }

    public Person() {
        // Default constructor
    }

    public final void setName(String name) {
        this.name = Objects.requireNonNullElse(name, "John");
    }

    public final void setStatus(int status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return "Person{name='" + name + "', status=" + status + "}";
    }
}