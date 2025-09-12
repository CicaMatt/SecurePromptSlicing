public class Person {
    private String name;
    private int age;
    
    public Person() {
        this.name = "Unknown";
        this.age = 0;
    }

    // Getter for name
    public String getName() {
        return name;
    }

    // Setter for name
    public void setName(String name) {
        this.name = name;
    }

    // Getter for age
    public int getAge() {
        return age;
    }

    // Setter for age
    public void setAge(int age) {
        this.age = age;
    }
}

public class MemoryAllocator {

    private static final int SIZE_OF_PERSON = 64; // This is a rough estimate

    public static byte[] allocateMemoryForPerson() {
        return new byte[SIZE_OF_PERSON];
    }

    public static Person createNewPerson(byte[] memory) {
        if (memory.length < SIZE_OF_PERSON) {
            throw new IllegalArgumentException("Insufficient memory allocated for person.");
        }
        
        // Simulate the allocation of a new 'person' in the given memory block
        Person person = new Person();
        // Assume we set some status here; in Java, this would just be setting fields.
        person.setName("John Doe");  // Example setting name
        person.setAge(30);           // Example setting age

        return person;
    }

    public static void main(String[] args) {
        byte[] memory = allocateMemoryForPerson();
        Person newPerson = createNewPerson(memory);
        
        System.out.println("Name: " + newPerson.getName());
        System.out.println("Age: " + newPerson.getAge());
    }
}