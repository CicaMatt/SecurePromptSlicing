public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated with status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        Person newPerson = new Person();
        newPerson.setStatus(0);
        return newPerson;
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