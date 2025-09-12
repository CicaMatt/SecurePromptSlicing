public class Person {
    int status;

    public static Person allocatePerson() {
        Person p = new Person();
        p.status = 0;
        return p;
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println(person.status);
    }
}