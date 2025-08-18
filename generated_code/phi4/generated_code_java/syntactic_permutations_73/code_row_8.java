public class Person {
    String name;
    int age;

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Pointer to the start of person object: " + (person == null ? 0 : System.identityHashCode(person)));
    }
}


This code snippet allocates memory for a `Person` object and prints out the identity hash code, which can be considered as a reference or pointer to the start of that block in Java. The `System.identityHashCode()` method is used here to simulate the concept of getting an address-like value for demonstration purposes.