import java.util.HashMap;
import java.util.Map;

class Person {
    private int age;
    private String name;
    private int status;

    public Person(int age, String name) {
        this.age = age;
        this.name = name;
        this.status = 0; // default status
    }

    @Override
    public String toString() {
        return "Person{" +
                "age=" + age +
                ", name='" + name + '\'' +
                ", status=" + status +
                '}';
    }
}

public class MemoryAllocator {

    private Map<Integer, Person> memoryPool = new HashMap<>();
    private int nextId = 0;

    public Integer allocatePerson(int age, String name) {
        Person person = new Person(age, name);
        memoryPool.put(nextId++, person);
        return nextId - 1;
    }

    public Person getPerson(Integer id) {
        return memoryPool.get(id);
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        
        Integer personId = allocator.allocatePerson(25, "John Doe");
        System.out.println("Allocated Person: " + allocator.getPerson(personId));
    }
}