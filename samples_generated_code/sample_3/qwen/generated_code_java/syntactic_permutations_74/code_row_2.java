public class PersonAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated with status: " + person.status);
    }

    public static Person allocatePerson() {
        return new Person();
    }
}

class Person {
    int status;

    public Person() {
        this.status = 0;
    }
}