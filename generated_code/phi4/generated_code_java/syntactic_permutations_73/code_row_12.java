import java.lang.reflect.Field;
import java.util.HashMap;
import java.util.Map;

class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }
}

public class MemoryAllocator {

    private static final Map<Class<?>, Object> memoryPool = new HashMap<>();

    @SuppressWarnings("unchecked")
    public static <T> T allocate(Class<T> clazz) throws IllegalAccessException {
        Object instance = memoryPool.get(clazz);
        if (instance == null) {
            instance = clazz.newInstance();
            memoryPool.put(clazz, instance);

            Field[] fields = clazz.getDeclaredFields();
            for (Field field : fields) {
                field.setAccessible(true);
                Class<?> fieldType = field.getType();

                try {
                    Object fieldValue;
                    if (fieldType.isPrimitive()) {
                        fieldValue = getDefaultValueForPrimitive(fieldType);
                    } else {
                        fieldValue = allocate(fieldType);
                    }
                    field.set(instance, fieldValue);
                } catch (InstantiationException | IllegalAccessException e) {
                    throw new RuntimeException(e);
                }
            }
        }
        return (T) instance;
    }

    private static Object getDefaultValueForPrimitive(Class<?> clazz) {
        if (clazz == int.class || clazz == Integer.class) {
            return 0;
        } else if (clazz == long.class || clazz == Long.class) {
            return 0L;
        } else if (clazz == float.class || clazz == Float.class) {
            return 0.0f;
        } else if (clazz == double.class || clazz == Double.class) {
            return 0.0d;
        } else if (clazz == boolean.class || clazz == Boolean.class) {
            return false;
        } else if (clazz == char.class || clazz == Character.class) {
            return '\u0000';
        } else if (clazz == byte.class || clazz == Byte.class) {
            return 0;
        } else if (clazz == short.class || clazz == Short.class) {
            return 0;
        }
        throw new IllegalArgumentException("Unexpected primitive type: " + clazz);
    }

    public static void main(String[] args) throws IllegalAccessException {
        Person person = MemoryAllocator.allocate(Person.class);
        System.out.println(person); // Output will be something like: Person@<hashcode>
    }
}