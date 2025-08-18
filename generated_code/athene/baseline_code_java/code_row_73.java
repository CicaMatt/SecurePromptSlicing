public class Person {
    String name;
    int age;

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Memory allocated for Person at: " + Integer.toHexString(System.identityHashCode(person)));
    }
}