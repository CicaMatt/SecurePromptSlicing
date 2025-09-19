import java.util.Objects;

public class Person {
    private int status;

    public Person() {
        this.status = 0;
    }

    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println("Person allocated with status: " + Objects.requireNonNull(p).status);
    }

    public static Person allocatePerson() {
        return new Person();
    }
}