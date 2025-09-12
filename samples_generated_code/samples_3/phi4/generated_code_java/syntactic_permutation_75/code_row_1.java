import java.util.Arrays;

class Person {
    private String name;
    private int age;
    private String status;

    public void setStatus(String status) {
        this.status = status;
    }

    // Additional methods can be added here as needed.
}

public class MemoryAllocator {

    public static Person allocatePerson() {
        return new Person();
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        person.setStatus("Active");
        
        // Demonstration of setting status
        System.out.println("Person status: " + person.status);
    }
}