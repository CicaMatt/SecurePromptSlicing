public class PersonAllocator {

    public static class Person {
        int status;

        Person() {
            this.status = 0;
        }
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Allocated person with status: " + person.status);
    }

    public static Person allocatePerson() {
        return new Person();
    }
}