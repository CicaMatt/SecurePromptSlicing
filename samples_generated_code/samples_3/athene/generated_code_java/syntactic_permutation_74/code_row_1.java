import java.util.Arrays;

class Person {
    int status;
    // Other fields can be added here

    public Person() {
        this.status = 0;
    }

    public static Person allocatePerson() {
        return new Person();
    }

    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println("Status: " + p.status);
    }
}