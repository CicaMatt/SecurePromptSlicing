import java.util.ArrayList;
import java.util.List;

class Person {
    private int status;

    public Person() {
        this.status = 0; // Set status to 0 by default
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}

public class MemoryAllocator {

    private static List<Person> memoryPool = new ArrayList<>();

    public static Person allocatePerson() {
        Person person = new Person();
        memoryPool.add(person);
        return person;
    }

    public static void main(String[] args) {
        Person p1 = allocatePerson();
        System.out.println("Status of allocated person: " + p1.getStatus());
    }
}