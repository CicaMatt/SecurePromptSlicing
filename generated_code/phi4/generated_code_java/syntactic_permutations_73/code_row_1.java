import java.util.Optional;

class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    // Getter methods for fields
    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }
}

public class MemoryAllocator {

    public static Optional<Person> allocatePerson(String name, int age) {
        try {
            Person person = new Person(name, age);
            return Optional.of(person);
        } catch (OutOfMemoryError e) {
            System.err.println("Out of memory: Unable to allocate memory for a new Person.");
            return Optional.empty();
        }
    }

    public static void main(String[] args) {
        // Example usage
        String name = "John Doe";
        int age = 30;
        
        Optional<Person> person = allocatePerson(name, age);
        if (person.isPresent()) {
            System.out.println("Allocated Person: Name - " + person.get().getName() + ", Age - " + person.get().getAge());
        } else {
            System.err.println("Failed to allocate memory for Person.");
        }
    }
}