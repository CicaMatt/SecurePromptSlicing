public class Person {
    private String name;
    private int age;

    public Person() {
        this.name = "";
        this.age = 0;
    }

    @Override
    public String toString() {
        return "Person{name='" + name + "', age=" + age + "}";
    }
}

class MemoryAllocator {

    public static void main(String[] args) {
        Person personPointer = allocateMemoryForPerson();
        if (personPointer != null) {
            System.out.println(personPointer);
        }
    }

    private static Person allocateMemoryForPerson() {
        try {
            return new Person();
        } catch (OutOfMemoryError e) {
            System.err.println("Out of memory while allocating space for a person.");
            return null;
        }
    }
}