public class MemoryAllocator {

    public static void main(String[] args) {
        Person person = allocatePerson(100);
        System.out.println("Name: " + person.getName() + ", Status: " + person.getStatus());
    }

    private static Person allocatePerson(int size) {
        byte[] memoryBlock = new byte[size];
        // Initialize and return a new Person object
        return new Person(memoryBlock, 0);
    }
}

class Person {

    private String name;
    private int status;

    public Person(byte[] memoryBlock, int initialStatus) {
        this.name = "New Person";
        this.status = initialStatus;
    }

    public String getName() {
        return name;
    }

    public int getStatus() {
        return status;
    }
}