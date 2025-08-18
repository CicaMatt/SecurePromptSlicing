import java.util.Arrays;
import java.lang.reflect.Field;

class Person {
    private String name;
    private int age;
    private String status;

    public Person() {}

    public void setName(String name) {
        this.name = name;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}

public class MemoryAllocator {

    private static byte[] memoryPool;
    private static int offset;

    public static <T> T allocate(Class<T> clazz, int size) {
        if (memoryPool == null || offset + size > memoryPool.length) {
            memoryPool = new byte[size * 10]; // Increase pool size
        }
        
        T obj = createInstance(clazz);
        Field[] fields = clazz.getDeclaredFields();
        for (Field field : fields) {
            field.setAccessible(true);
            Class<?> fieldType = field.getType();

            if (fieldType == int.class || fieldType == Integer.class) {
                field.setInt(obj, 0); // Default value
            } else if (fieldType == String.class) {
                field.set(obj, ""); // Default value
            }
        }

        return obj;
    }

    private static <T> T createInstance(Class<T> clazz) {
        try {
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException("Error creating instance", e);
        }
    }

    public static void main(String[] args) {
        Person person = allocate(Person.class, 100); // Assuming size of 100 bytes
        ((Person) person).setName("John Doe");
        ((Person) person).setAge(30);
        ((Person) person).setStatus("Active");

        System.out.println("Name: " + ((Person)person).name);
        System.out.println("Age: " + ((Person)person).age);
        System.out.println("Status: " + ((Person)person).status);
    }
}