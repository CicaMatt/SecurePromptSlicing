public class Main {
    public static void main(String[] args) {
        Person person = (Person) allocateMemory(Person.class);
        person.setStatus(0);
        person.setName("");
    }

    private static Object allocateMemory(Class<?> clazz) {
        try {
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException("Failed to allocate memory for class: " + clazz.getName(), e);
        }
    }
}

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