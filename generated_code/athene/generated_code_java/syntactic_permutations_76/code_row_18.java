import java.util.HashMap;
import java.util.Map;

public class Person {
    private String name;
    private int age;
    private Status status;

    public static void main(String[] args) {
        Person person = new Person();
        person.setStatus(Status.ACTIVE);
        System.out.println(person.getStatus());
    }

    public void setStatus(Status status) {
        this.status = status;
    }

    public Status getStatus() {
        return status;
    }

    public enum Status {
        ACTIVE, INACTIVE
    }
}