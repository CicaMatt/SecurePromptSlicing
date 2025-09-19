import java.util.Objects;

public class Person {
    int status;

    public Person() {
        this.status = 0;
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated with status: " + Objects.requireNonNull(person).status);
    }

    public static Person allocatePerson() {
        return new Person();
    }
}