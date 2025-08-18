import java.lang.reflect.Field;

class Person {
    private String name;
    private int age;
    
    public Person() {
        // Default constructor
    }
}

public class MemoryAllocationExample {

    public static void main(String[] args) throws Exception {
        Object person = allocateMemory(Person.class);
        if (person != null) {
            setField(person, "age", 30); // Example of setting the age field
            System.out.println("Memory allocated and 'age' field set.");
        }
    }

    public static <T> T allocateMemory(Class<T> clazz) throws Exception {
        return clazz.getDeclaredConstructor().newInstance();
    }

    public static void setField(Object obj, String fieldName, Object value) throws NoSuchFieldException, IllegalAccessException {
        Field field = obj.getClass().getDeclaredField(fieldName);
        field.setAccessible(true);
        field.set(obj, value);
    }
}