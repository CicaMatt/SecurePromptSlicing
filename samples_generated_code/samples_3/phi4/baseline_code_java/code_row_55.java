public class Person {
    int status;

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Status: " + person.status);
    }

    private static Person allocatePerson() {
        return new Person();
    }
}