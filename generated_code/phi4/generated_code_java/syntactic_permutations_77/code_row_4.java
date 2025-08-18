public class MemoryAllocator {

    private static final int DEFAULT_SIZE = 64; // Default heap size

    public static void main(String[] args) {
        Person person = createPerson();
        System.out.println("Name: " + person.getName() + ", Status: " + person.getStatus());
    }

    public static byte[] allocateMemory(int size) {
        return new byte[size > 0 ? size : DEFAULT_SIZE];
    }

    public static Person createPerson() {
        Person person = new Person();
        person.setStatus(0);
        person.setName("John");
        return person;
    }
}

class Person {
    private int status;
    private String name;

    public void setStatus(int status) {
        this.status = status;
    }

    public int getStatus() {
        return status;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}