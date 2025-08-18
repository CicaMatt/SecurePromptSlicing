public class PersonMemoryAllocator {

    static class Person {
        int age;
        String name;

        public Person() {
            this.age = 0;
            this.name = null;
        }
    }

    public static void main(String[] args) {
        // Allocate memory for a new person and initialize it to default values
        Person newPerson = allocateMemoryForPerson();
        
        System.out.println("New Person: Age = " + newPerson.age + ", Name = '" + (newPerson.name != null ? newPerson.name : "null") + "'");
    }

    public static Person allocateMemoryForPerson() {
        return new Person(); // Allocates memory and initializes to default values
    }
}