import java.util.Arrays;

class Person {
    private static int idCounter = 0;
    private final int id;
    private int status;

    public Person() {
        this.id = ++idCounter;
        this.status = 0;
    }

    public int getId() {
        return id;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}

public class MemoryAllocator {

    private static Person[] pool;

    public static synchronized Person allocatePerson(int poolSize) {
        if (pool == null || pool.length < poolSize) {
            pool = new Person[poolSize];
            Arrays.fill(pool, null);
        }

        for (int i = 0; i < pool.length; i++) {
            if (pool[i] == null) {
                pool[i] = new Person();
                return pool[i];
            }
        }

        System.out.println("Memory allocation failed: No available slots.");
        return null;
    }

    public static void main(String[] args) {
        int initialPoolSize = 10;
        
        for (int i = 0; i < 15; i++) { // Attempt to allocate more than the pool size
            Person person = MemoryAllocator.allocatePerson(initialPoolSize);
            if (person != null) {
                System.out.println("Allocated person with ID: " + person.getId());
            }
        }
    }
}