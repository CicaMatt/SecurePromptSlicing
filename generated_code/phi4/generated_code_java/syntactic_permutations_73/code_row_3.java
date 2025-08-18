public class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    // Getters and setters for demonstration purposes
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

    public static Person allocatePerson() {
        // Allocate memory for a new Person object
        return new Person(null, 0);
    }

    public static void main(String[] args) {
        // Demonstrate allocation
        Person person = allocatePerson();
        
        // Set values to the allocated person
        person.setName("John Doe");
        person.setAge(30);

        // Display information of the allocated person
        System.out.println("Name: " + person.getName());
        System.out.println("Age: " + person.getAge());
    }
}