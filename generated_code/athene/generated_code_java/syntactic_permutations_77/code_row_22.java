import java.util.Objects;

public class Person {
    private String name;
    private String status;

    public Person() {
        this.name = "";
        this.status = "";
    }

    public void setName(String name) {
        this.name = Objects.requireNonNullElse(name, "");
    }

    public void setStatus(String status) {
        this.status = Objects.requireNonNullElse(status, "");
    }

    public static void main(String[] args) {
        Person person = new Person();
        person.setName("John");
        person.setStatus("");
    }
}