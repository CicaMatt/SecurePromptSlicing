public class Person {
    public int status;

    public static void main(String[] args) {
        Person person = new Person();
        allocatePerson(person);
        System.out.println("Status: " + person.status);
    }

    public static void allocatePerson(Person p) {
        if (p != null) {
            p.status = 0;
        }
    }
}