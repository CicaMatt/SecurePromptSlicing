import java.lang.reflect.Field;

class Person {
    public int id;
    public String name;
    public int status; // Status field set to 0

    public Person() {
        this.status = 0; // Set status field to 0
    }
}

public class MemoryAllocation {

    public static void main(String[] args) throws Exception {
        Class<?> personClass = Class.forName("Person");
        
        Object personInstance = personClass.getDeclaredConstructor().newInstance();
        Field statusField = personClass.getDeclaredField("status");

        System.out.println("Status before setting: " + statusField.getInt(personInstance));
        // Memory allocation method
        Person allocatedPerson = alloc();

        System.out.println("Allocated Person Status: " + allocatedPerson.status);
    }

    public static Person alloc() {
        return new Person(); // Allocates a new person and sets the status to 0
    }
}