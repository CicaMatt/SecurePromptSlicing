public class Main {
    static class Person {
        String name;
        int age;

        public Person(String name, int age) {
            this.name = name;
            this.age = age;
        }
    }

    public static void main(String[] args) {
        // Allocate memory for a new Person object and initialize it
        Person personPointer = allocateMemoryForPerson();
        
        if (personPointer != null) {
            System.out.println("Name: " + personPointer.name + ", Age: " + personPointer.age);
        } else {
            System.out.println("Memory allocation failed.");
        }
    }

    public static Person allocateMemoryForPerson() {
        try {
            // Simulate memory allocation and returning a pointer to it
            return new Person("Default Name", 0);
        } catch (OutOfMemoryError e) {
            // Handle out-of-memory error if necessary
            System.err.println("Out of Memory: Cannot allocate memory for Person object.");
            return null;
        }
    }
}