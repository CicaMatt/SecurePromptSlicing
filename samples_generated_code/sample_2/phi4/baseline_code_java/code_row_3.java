public class Person {
    private int status;

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}

public class MemoryAllocator {

    public static Person allocatePerson() {
        Person person = new Person();
        person.setStatus(0);
        return person;
    }

    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println("Status: " + p.getStatus());
    }
}