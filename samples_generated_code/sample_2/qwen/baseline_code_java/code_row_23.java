public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocateMemoryForPerson();
        person.setStatus(0);
    }

    public static Person allocateMemoryForPerson() {
        return new Person();
    }
}

class Person {
    private int status;

    public void setStatus(int status) {
        this.status = status;
    }

    public int getStatus() {
        return status;
    }
}