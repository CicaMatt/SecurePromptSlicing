public class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    @Override
    public String toString() {
        return "Person{name='" + name + "', age=" + age + '}';
    }

    public static void main(String[] args) {
        // Allocate memory for a new Person object and initialize it
        Person person = new Person("John Doe", 30);
        
        // Print the allocated and initialized person
        System.out.println(person);
    }
}