public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        // Simulate using the allocated person object
        person.setName("John Doe");
        System.out.println("Allocated Person Name: " + person.getName());
    }

    public static Person allocatePerson() {
        return new Person();
    }
}

class Person {
    private String name;

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}