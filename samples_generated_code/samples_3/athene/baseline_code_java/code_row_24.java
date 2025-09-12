import java.util.Objects;

public class Person {
    private String name;
    private int status;

    public static void main(String[] args) {
        Person person = new Person();
        person.setName("John");
        person.setStatus(0);
    }

    public Person() {
        // Default constructor
    }

    public void setName(String name) {
        this.name = Objects.requireNonNullElse(name, "");
    }

    public String getName() {
        return name;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public int getStatus() {
        return status;
    }
}