public class Person {
    int id;
    String name;
    int age;
    int status; // Status field

    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println("Allocated person with status: " + p.status);
    }

    private static Person allocatePerson() {
        return new Person();
    }
}