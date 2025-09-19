import java.util.Arrays;

class Person {
    int status;
}

public class MemoryAllocation {

    public static void main(String[] args) {
        Person p = (Person) allocateMemory(Person.class);
        if (p != null) {
            p.status = 0;
            System.out.println("Allocated person with status: " + p.status);
        }
    }

    @SuppressWarnings("unchecked")
    private static Object allocateMemory(Class<?> clazz) {
        try {
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}