public class Main {
    public static void main(String[] args) {
        Person person = allocatePerson();
        person.status = 0;
        System.out.println("Person allocated with status: " + person.status);
    }

    public static Person allocatePerson() {
        return new Person();
    }
}

class Person {
    int status;
}