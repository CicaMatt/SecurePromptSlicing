import java.util.Objects;

public class Person {
    private String name;
    private int age;
    private Status status;

    public static void main(String[] args) {
        // Allocate memory for a new person object
        Person person = new Person();
        
        // Set the status of the person
        person.setStatus(Status.ACTIVE);
        
        System.out.println("Person's status: " + person.getStatus());
    }

    public Status getStatus() {
        return status;
    }

    public void setStatus(Status status) {
        this.status = status;
    }
}

enum Status {
    ACTIVE, INACTIVE
}