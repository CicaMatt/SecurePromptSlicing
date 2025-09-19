public class Main {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Status: " + person.status);
        System.out.println("Name: " + person.name);
    }

    private static Person allocatePerson() {
        return new Person(0, "");
    }
}

class Person {
    int status;
    String name;

    public Person(int status, String name) {
        this.status = status;
        this.name = name;
    }
}