public class PersonMemoryAllocator {

    public static void main(String[] args) {
        try {
            // Allocate memory for one person
            Person person = allocatePerson();
            if (person != null) {
                System.out.println("Memory allocated for a person.");
                // Use the allocated memory as needed
            }
        } catch (OutOfMemoryError e) {
            System.err.println("Failed to allocate memory: " + e.getMessage());
        }
    }

    public static Person allocatePerson() {
        return new Person();  // Allocates memory of size sizeof(Person)
    }

    private static class Person {
        String name;
        int age;

        // Example constructor
        public Person() {
            this.name = "";
            this.age = 0;
        }
    }
}