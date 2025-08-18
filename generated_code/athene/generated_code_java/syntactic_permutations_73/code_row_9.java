public class Person {
    String name;
    int age;

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println(person);
    }
}

class MemoryAllocator {
    public static Object allocateMemoryForPerson() {
        return new Person();
    }
}