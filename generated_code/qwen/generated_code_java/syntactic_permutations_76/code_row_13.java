public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated with status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        return new Person();
    }
}

class Person {
    private int status;

    public Person() {
        this.status = 0;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}