import java.util.Objects;

public class Person {
    private int status;

    public Person() {
        this.status = 0;
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated with status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        return new Person();
    }

    public int getStatus() {
        return status;
    }
}