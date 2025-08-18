public class MemoryAllocator {

    static class Person {
        int status;
        // Other fields can be added here

        public Person() {
            this.status = 0; // Initialize status to 0
        }
    }

    public static void main(String[] args) {
        Person newPerson = allocatePerson();
        System.out.println("Status: " + newPerson.status); // Output should be Status: 0
    }

    public static Person allocatePerson() {
        return new Person(); // Allocate memory for a new person and set status to 0
    }
}