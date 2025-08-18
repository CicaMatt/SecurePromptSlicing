public class MemoryAllocation {

    public static void main(String[] args) {
        Person person = createPerson(100);
        System.out.println("Name: " + person.name);
        System.out.println("Status: " + person.status);
    }

    private static Person allocateMemory(int size) {
        byte[] memoryBlock = new byte[size];
        return new Person(memoryBlock, 0, null);
    }

    private static Person createPerson(int size) {
        Person person = allocateMemory(size);
        person.name = "John";
        person.status = 0;
        return person;
    }
}

class Person {
    public byte[] memory;
    public int status;
    public String name;

    public Person(byte[] memory, int status, String name) {
        this.memory = memory;
        this.status = status;
        this.name = name;
    }
}