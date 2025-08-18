public class MemoryAllocator {
    static class Person {
        int status;
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        person.status = 0;
    }

    private static Person allocatePerson() {
        return new Person();
    }
}