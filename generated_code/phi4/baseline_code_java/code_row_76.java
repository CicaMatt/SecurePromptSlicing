public class PersonAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated with status: " + person.status);
    }

    private static Person allocatePerson() {
        return new Person(0);
    }
}

class Person {
    int status;

    public Person(int status) {
        this.status = status;
    }
}