class Person {
    int status;
}

public class Main {
    public static void main(String[] args) {
        // Allocate a new person and set its status field to 0
        Person p = new Person();
        p.status = 0;

        System.out.println("Person status: " + p.status);
    }
}