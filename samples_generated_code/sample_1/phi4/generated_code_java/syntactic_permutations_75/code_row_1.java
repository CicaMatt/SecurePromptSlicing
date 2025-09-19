public class Person {
    int status;

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("New person created with status: " + person.status);
    }

    private static Person allocatePerson() {
        return new Person();
    }
}