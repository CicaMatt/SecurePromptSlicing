public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocateMemory();
        System.out.println("Person object allocated at: " + System.identityHashCode(person));
    }

    public static Person allocateMemory() {
        return new Person();
    }
}

class Person {
    private String name;
    private int age;

    // Constructor
    public Person() {
        this.name = "Default Name";
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