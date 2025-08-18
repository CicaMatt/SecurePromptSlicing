public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = allocatePerson();
        person.setStatus(0);
        System.out.println("Person status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        return new Person();
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