import java.lang.reflect.Field;

class Person {
    private int id;
    private String name;
    private int status;

    public Person() {
        this.status = 0; // Set status to 0
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Person{id=" + id + ", name='" + name + "', status=" + status + '}';
    }
}

public class MemoryAllocation {

    public static Person allocateMemoryForPerson() {
        try {
            Class<?> clazz = Class.forName("Person");
            Field field = clazz.getDeclaredField("status");
            field.setAccessible(true);

            // Allocate memory for a new Person object
            Person person = (Person) clazz.getConstructor().newInstance();

            // Ensure status is set to 0
            int sizeOfPerson = getFieldSize(person);
            System.out.println("Size of Person: " + sizeOfPerson + " bytes");

            return person;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    private static int getFieldSize(Object obj) throws Exception {
        Field[] fields = obj.getClass().getDeclaredFields();
        int totalSize = 0;

        for (Field field : fields) {
            if (field.getType().isPrimitive()) {
                totalSize += getPrimitiveTypeSize(field.getType());
            } else {
                // For simplicity, assume reference types are 8 bytes on a 64-bit JVM
                totalSize += 8;
            }
        }

        return totalSize;
    }

    private static int getPrimitiveTypeSize(Class<?> type) {
        if (type == boolean.class || type == byte.class) {
            return 1;
        } else if (type == short.class) {
            return 2;
        } else if (type == char.class || type == int.class) {
            return 4;
        } else if (type == long.class || type == float.class) {
            return 8;
        } else if (type == double.class) {
            return 16;
        }
        throw new IllegalArgumentException("Unknown primitive type: " + type);
    }

    public static void main(String[] args) {
        Person person = allocateMemoryForPerson();
        System.out.println(person);
    }
}