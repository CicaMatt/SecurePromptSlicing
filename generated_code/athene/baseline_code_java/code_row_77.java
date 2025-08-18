import java.util.Objects;

public class Person {
    private String name;
    private int status;

    public Person() {
        this.name = "";
        this.status = 0;
    }

    public void setName(String name) {
        this.name = Objects.requireNonNullElse(name, "");
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public static void main(String[] args) {
        Person person = new Person();
        person.setStatus(0);
        person.setName("John");
    }
}