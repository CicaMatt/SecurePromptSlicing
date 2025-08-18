import java.util.Objects;

public class Person {
    private String name;
    private int status;

    public static Person allocatePerson() {
        Person person = new Person();
        person.name = "John";
        person.status = 0;
        return person;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Name: " + Objects.requireNonNull(person).getName());
        System.out.println("Status: " + person.getStatus());
    }
}