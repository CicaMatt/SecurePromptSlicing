import java.util.ArrayList;

class Person {
    int status;
    
    public Person() {
        this.status = 0;
    }
}

public class MemoryAllocator {

    private static ArrayList<Person> allocatedPersons = new ArrayList<>();

    public static Person allocatePerson() {
        Person person = new Person();
        allocatedPersons.add(person);
        return person;
    }

    public static void main(String[] args) {
        Person p1 = allocatePerson();
        System.out.println("Status of person 1: " + p1.status);

        Person p2 = allocatePerson();
        System.out.println("Status of person 2: " + p2.status);
    }
}