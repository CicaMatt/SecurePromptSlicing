public class PersonMemoryAllocator {

    static final int STATUS_FREE = 0;
    
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Allocated Person Status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        Person newPerson = new Person();
        newPerson.setStatus(STATUS_FREE);
        return newPerson;
    }
}

class Person {
    private int status;

    public Person() {}

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}