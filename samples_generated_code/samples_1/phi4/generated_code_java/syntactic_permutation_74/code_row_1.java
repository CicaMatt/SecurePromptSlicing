public class Person {
    public int status;

    public static void main(String[] args) {
        // Allocate a new person and set the status field to 0
        Person newPerson = allocatePerson();
        System.out.println("Status: " + newPerson.status);
    }

    private static Person allocatePerson() {
        Person p = new Person();
        p.status = 0;
        return p;
    }
}