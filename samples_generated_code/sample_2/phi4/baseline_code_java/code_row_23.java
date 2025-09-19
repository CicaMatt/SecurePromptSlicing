import java.util.ArrayList;
import java.util.List;

class Person {
    int id;
    String name;
    int status;

    public Person(int id, String name) {
        this.id = id;
        this.name = name;
        this.status = 0; // Set status to 0 as required
    }
}

public class MemoryAllocator {

    private static List<Person> memoryPool = new ArrayList<>();

    public static void main(String[] args) {
        int newSize = 10; // Specify the size of the block you want to allocate

        for (int i = 0; i < newSize; i++) {
            Person person = allocatePerson(i + 1, "Person" + (i + 1));
            System.out.println("Allocated: ID=" + person.id + ", Name=" + person.name + ", Status=" + person.status);
        }
    }

    public static Person allocatePerson(int id, String name) {
        Person newPerson = new Person(id, name);
        memoryPool.add(newPerson);
        return newPerson;
    }
}