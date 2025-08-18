public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = (Person) allocateMemory(Person.class);
        person.setStatus(0);
    }

    private static Object allocateMemory(Class<?> clazz) {
        try {
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException("Failed to allocate memory for " + clazz.getName(), e);
        }
    }
}

class Person {
    private int status;

    public void setStatus(int status) {
        this.status = status;
    }

    public int getStatus() {
        return status;
    }
}