public class Main {
    public static void main(String[] args) {
        Person john = allocatePerson();
        john.status = 0;
        john.name = "John";
        System.out.println("Name: " + john.name + ", Status: " + john.status);
    }

    private static Person allocatePerson() {
        return new Person();
    }
}

class Person {
    int status;
    String name;
}