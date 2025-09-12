public class PersonAllocator {

    static class Person {
        int status;
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated with status: " + person.status);
    }

    public static Person allocatePerson() {
        Person person = new Person();
        person.status = 0;
        return person;
    }
}