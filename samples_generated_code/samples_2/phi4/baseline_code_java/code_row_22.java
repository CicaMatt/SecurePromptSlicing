public class Person {
    private int id;
    private String name;
    private boolean status;

    public Person(int id, String name) {
        this.id = id;
        this.name = name;
        this.status = false; // Set status to 0 (false)
    }

    @Override
    public String toString() {
        return "Person{id=" + id + ", name='" + name + '\'' + ", status=" + status + '}';
    }
}

public class MemoryAllocator {

    private static int nextId = 1;

    public static Person allocatePerson(String name) {
        // Allocate memory for a new person
        Person newPerson = new Person(nextId++, name);
        
        // Return the pointer (reference) to the beginning of the block
        return newPerson;
    }

    public static void main(String[] args) {
        Person p = MemoryAllocator.allocatePerson("John Doe");
        System.out.println(p);

        // Change status to 1 (true)
        p = new Person(p.id, p.name);
        p.status = true;
        System.out.println(p);
    }
}