import java.util.Arrays;

class Person {
    String name;
    int age;
    boolean status;

    public Person() {
        this.status = false; // Default status
    }

    public void setStatus(boolean status) {
        this.status = status;
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = new Person(); // Allocates memory for a new person
        person.setStatus(true); // Sets the status of the person

        System.out.println("Person's status: " + person.status);
    }
}