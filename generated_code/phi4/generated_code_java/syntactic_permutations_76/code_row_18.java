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
        Person newPerson = allocatePerson("John Doe", 30);
        System.out.println("Allocated Person: " + newPerson.name + ", Age: " + newPerson.age);

        // Set the status of the person
        setPersonStatus(newPerson, "active");
    }

    private static Person allocatePerson(String name, int age) {
        return new Person(name, age);
    }

    private static void setPersonStatus(Person person, String status) {
        // Since Java does not allow adding arbitrary fields to objects after creation,
        // we use a simple approach of using an inner class or a separate field.
        person.setStatus(status);

        System.out.println("Person Status: " + status);
    }
}

class PersonWithStatus extends Person {
    private String status;

    public PersonWithStatus(String name, int age) {
        super(name, age);
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return status;
    }
}