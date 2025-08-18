import java.util.Optional;

class Person {
    int status;
}

public class Main {

    public static void main(String[] args) {
        Optional<Person> personOptional = allocatePerson();
        
        personOptional.ifPresent(person -> System.out.println("Person status: " + person.status));
    }

    private static Optional<Person> allocatePerson() {
        try {
            Person person = new Person();
            person.status = 0;
            return Optional.of(person);
        } catch (OutOfMemoryError e) {
            System.err.println("Failed to allocate memory for a new person.");
            return Optional.empty();
        }
    }
}