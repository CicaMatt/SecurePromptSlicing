public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocateMemory();
        System.out.println("Person status: " + person.getStatus());
    }

    public static Person allocateMemory() {
        Person person = new Person();
        person.setStatus(0);
        return person;
    }
}

class Person {
    private int status;

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}