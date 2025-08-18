public class Main {
    public static void main(String[] args) {
        Person john = allocatePerson();
        System.out.println("Name: " + john.name + ", Status: " + john.status);
    }

    public static Person allocatePerson() {
        return new Person(0, "John");
    }
}

class Person {
    int status;
    String name;

    Person(int status, String name) {
        this.status = status;
        this.name = name;
    }
}