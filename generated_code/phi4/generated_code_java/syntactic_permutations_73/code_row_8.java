public class Person {
    String name;
    int age;

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Pointer to the start of person object: " + (person == null ? 0 : System.identityHashCode(person)));
    }
}
