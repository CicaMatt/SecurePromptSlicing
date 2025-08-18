import java.util.ArrayList;

class Person {
    int status;
}

public class MemoryAllocator {

    private static final ArrayList<Person> memoryPool = new ArrayList<>();

    public static Person allocatePerson() {
        Person p = new Person();
        p.status = 0;
        memoryPool.add(p);
        return p;
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Allocated Person with status: " + person.status);
    }
}