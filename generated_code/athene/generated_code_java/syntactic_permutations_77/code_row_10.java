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
        // Allocate memory and initialize fields
        this.name = null;
        this.status = 0;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = Objects.requireNonNullElse(name, "Unknown");
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return "Person{name='" + name + "', status=" + status + "}";
    }
}