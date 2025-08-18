import java.util.Objects;

public class Person {
    private int status;

    public Person() {
        this.status = 0;
    }

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Person allocated with status: " + person.getStatus());
    }

    public int getStatus() {
        return status;
    }
}