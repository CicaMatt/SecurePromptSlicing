public class Person {
    int age;
    String name;
    int status;

    public static void main(String[] args) {
        Person person = new Person();
        person.status = 0;
        System.out.println("New person created with status: " + person.status);
    }
}