class Person {
    String name;
    int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate memory for a new person object
        @SuppressWarnings("unchecked")
        Person person = (Person) allocate(sizeof(Person.class));

        // Initialize the allocated memory with values
        if (person != null) {
            person.name = "John Doe";
            person.age = 30;
            
            System.out.println("Name: " + person.name);
            System.out.println("Age: " + person.age);
        }
    }

    @SuppressWarnings("unchecked")
    private static Object allocate(int size) {
        // Simulate memory allocation by creating a new object
        if (size == sizeof(Person.class)) {
            return new Person(null, 0);
        } else {
            return null;
        }
    }

    @SuppressWarnings("rawtypes")
    private static int sizeof(Class c) {
        // Calculate the size of the class in bytes (simplified estimation)
        if (c == Person.class) {
            return 2 * Integer.BYTES + (new String(" ")).getBytes().length; // name: String, age: int
        }
        return -1;
    }
}