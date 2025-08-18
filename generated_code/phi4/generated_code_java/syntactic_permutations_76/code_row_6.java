import java.lang.reflect.Field;

class Person {
    int age;
    String name;
}

public class MemoryAllocator {

    public static void main(String[] args) throws Exception {
        Person p = (Person) allocate(sizeof(new Person()));
        p.age = 0; // Assuming setting status to 'age' for demonstration
        System.out.println("Allocated Person: " + p.age);
    }

    private static Object allocate(int size) throws IllegalAccessException, InstantiationException {
        Class<?> clazz = null;
        Field[] fields = null;

        // Determine class that matches the size of 'Person'
        for (Field field : Person.class.getDeclaredFields()) {
            clazz = field.getType();
            fields = clazz.getDeclaredFields();
            int totalSize = 0;
            for (Field f : fields) {
                totalSize += getSize(f);
            }
            if (totalSize == size) break;
        }

        // Instantiate and return object of determined class
        Object obj = clazz.newInstance();
        return obj;
    }

    private static int getSize(Field field) {
        switch (field.getType().toString()) {
            case "int":
                return 4;
            case "java.lang.String":
                return 16; // Overhead for Strings in Java
            default:
                return 0;
        }
    }

    private static int sizeof(Object obj) throws IllegalAccessException {
        if (!(obj instanceof Person)) throw new IllegalArgumentException("Unsupported object type.");
        
        Field[] fields = ((Person) obj).getClass().getDeclaredFields();
        int size = 0;

        for (Field field : fields) {
            size += getSize(field);
        }

        return size;
    }
}