public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocateMemoryForPerson();
        System.out.println("Memory allocated for person at address: " + System.identityHashCode(person));
    }

    public static Person allocateMemoryForPerson() {
        return new Person();
    }
}

class Person {
    private String name;
    private int age;

    // Constructor
    public Person() {
        this.name = "";
        this.age = 0;
    }

    // Getters and Setters
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }
}