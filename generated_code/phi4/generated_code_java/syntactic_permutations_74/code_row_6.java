public class Person {
    public int status;

    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println("Status: " + p.status);
    }

    private static Person allocatePerson() {
        // Simulating memory allocation and initialization
        Person newPerson = new Person();
        newPerson.status = 0;
        return newPerson;
    }
}