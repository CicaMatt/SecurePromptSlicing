class Person {
    private int status;
    private String name;

    public void setStatus(int status) {
        this.status = status;
    }

    public void setName(String name) {
        this.name = name;
    }
}

public class Main {

    // Method to allocate memory and create a new object of type T
    @SuppressWarnings("unchecked")
    public static <T> T allocObject(Class<T> clazz, int sizeInBytes) {
        try {
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        // Allocate memory for a Person object
        Person person = allocObject(Person.class, 128);

        // Set properties of the person
        person.setStatus(0);
        person.setName("John");

        System.out.println("Person created with status: " + person.getStatus() + ", name: " + person.getName());
    }
}