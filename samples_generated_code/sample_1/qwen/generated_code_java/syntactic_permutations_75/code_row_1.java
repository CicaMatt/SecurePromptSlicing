public class PersonAllocator {

    static class Person {
        int status;

        public Person(int status) {
            this.status = status;
        }
    }

    public static void main(String[] args) {
        Person newPerson = allocatePerson();
        System.out.println("Person allocated with status: " + newPerson.status);
    }

    public static Person allocatePerson() {
        return new Person(0);
    }
}