public class PersonMemoryAllocator {
    private static class Person {
        int status;
        
        public Person(int status) {
            this.status = status;
        }
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person status: " + person.status);
    }

    public static Person allocatePerson() {
        return new Person(0);
    }
}