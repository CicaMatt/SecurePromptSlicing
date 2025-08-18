import java.util.Objects;

public class Person {
    private int id;
    
    public Person() {
        this.id = 0;
    }

    public static void main(String[] args) {
        // Allocate memory for a new person object
        Person person = new Person();
        
        // Verify allocation and initialization
        System.out.println("Person ID: " + (Objects.isNull(person) ? "null" : person.id));
    }
}