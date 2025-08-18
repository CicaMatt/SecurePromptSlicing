public class Person {
    private int status;
    
    public Person() {
        this.status = 0;
    }
}

public class MemoryAllocator {

    public static void main(String[] args) {
        // Allocate memory for one Person object
        Person newPerson = allocate();
        
        // Check the initial status of the person
        System.out.println("Status: " + newPerson.getStatus());
    }

    public static Person allocate() {
        // Simulating allocation of memory and creation of a Person instance
        return new Person();
    }
}