import java.util.Arrays;

public class MemoryAllocation {

    static class Person {
        int status;
        String name;
        
        public Person(int status, String name) {
            this.status = status;
            this.name = name;
        }
    }

    public static void main(String[] args) {
        // Allocate memory for a single person
        Person newPerson = allocateMemoryForPerson();
        
        // Print the details of the newly created person
        System.out.println("Status: " + newPerson.status);
        System.out.println("Name: " + newPerson.name);
    }

    public static Person allocateMemoryForPerson() {
        return new Person(0, "John");
    }
}