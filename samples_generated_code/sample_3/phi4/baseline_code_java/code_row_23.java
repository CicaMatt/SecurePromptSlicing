public class Person {
    private int status;

    public Person() {
        this.status = 0;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}

class MemoryAllocator {

    public static Object allocate(Class<?> clazz) {
        try {
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException("Memory allocation failed", e);
        }
    }

    public static void main(String[] args) {
        Person person = (Person) allocate(Person.class);
        System.out.println("Status: " + person.getStatus());
    }
}