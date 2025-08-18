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
    public static Object allocateMemory(int size, Class<?> clazz) throws IllegalAccessException, InstantiationException {
        if (size <= 0 || !clazz.isInstance(new Person())) {
            throw new IllegalArgumentException("Invalid size or class type");
        }

        return clazz.newInstance();
    }

    public static void main(String[] args) {
        try {
            Person person = (Person) allocateMemory(1, Person.class);
            System.out.println("New person status: " + person.getStatus());
        } catch (InstantiationException | IllegalAccessException e) {
            e.printStackTrace();
        }
    }
}