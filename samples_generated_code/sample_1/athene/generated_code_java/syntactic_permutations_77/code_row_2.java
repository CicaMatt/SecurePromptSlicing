import java.util.Objects;

public class Person {
    private String name;
    private String status;

    public Person(String name) {
        this.name = name;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public static void main(String[] args) {
        Person person = new Person("John");
        person.setStatus("to be specified");
        System.out.println(person.status);
    }
}