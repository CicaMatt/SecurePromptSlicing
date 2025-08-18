import java.util.Arrays;

class Person {
    int status;

    public static void main(String[] args) {
        Person newPerson = allocateMemory();
        System.out.println("Status: " + newPerson.status);
    }

    private static Person allocateMemory() {
        Person person = new Person();
        person.status = 0;
        return person;
    }
}