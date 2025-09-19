public class PersonAllocator {

    static class Person {
        int status;
        // Other fields can be added here

        public Person() {
            this.status = 0; // Initialize status to 0
        }
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Allocated person with status: " + person.status);
    }

    public static Person allocatePerson() {
        return new Person(); // Allocate memory for a new Person and set status to 0
    }
}