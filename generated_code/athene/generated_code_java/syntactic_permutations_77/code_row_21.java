import java.util.Objects;

public class Person {
    private String name;

    public Person() {
        this.name = "";
    }

    public void setName(String name) {
        this.name = Objects.requireNonNullElse(name, "");
    }

    public String getName() {
        return name;
    }

    public static void main(String[] args) {
        Person person = new Person();
        person.setName("John");
        System.out.println(person.getName());
    }
}