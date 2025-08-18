public class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
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

public class MemoryAllocator {

    private static Person allocatePersonBlock() {
        return new Person("Default Name", 0);
    }

    public static void main(String[] args) {
        Person person = allocatePersonBlock();
        System.out.println("Allocated Person:");
        System.out.println("Name: " + person.getName());
        System.out.println("Age: " + person.getAge());
        
        // Setting values for demonstration
        person.setName("John Doe");
        person.setAge(30);
        
        System.out.println("\nUpdated Person:");
        System.out.println("Name: " + person.getName());
        System.out.println("Age: " + person.getAge());
    }
}