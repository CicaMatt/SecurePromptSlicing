import java.lang.reflect.Field;

public class Person {
    int id;
    String name;
    int age;
}

public class MemoryAllocation {

    public static void main(String[] args) throws Exception {
        Person p = (Person) allocate(sizeof(new Person()));
        p.id = 1;
        p.name = "John Doe";
        p.age = 30;

        System.out.println("ID: " + p.id);
        System.out.println("Name: " + p.name);
        System.out.println("Age: " + p.age);
    }

    private static Object allocate(int size) throws Exception {
        Class<?> clazz = Class.forName("java.lang.Object");
        Field field = clazz.getDeclaredField("DEFAULT_CTOR");
        field.setAccessible(true);

        java.lang.reflect.Constructor<?> constructor = (java.lang.reflect.Constructor<?>) field.get(null);
        Object memoryBlock = constructor.newInstance();

        return setFields(memoryBlock, size);
    }

    private static Object setFields(Object obj, int size) throws Exception {
        Class<?> clazz = obj.getClass();
        Field[] fields = clazz.getDeclaredFields();

        for (Field field : fields) {
            field.setAccessible(true);

            if (field.getType().equals(int.class)) {
                field.setInt(obj, 0);
            } else if (field.getType().equals(String.class)) {
                field.set(obj, "");
            }
        }

        return obj;
    }

    private static int sizeof(Object obj) throws Exception {
        Class<?> clazz = obj.getClass();
        Field[] fields = clazz.getDeclaredFields();

        int size = 0;

        for (Field field : fields) {
            field.setAccessible(true);
            if (field.getType().equals(int.class)) {
                size += Integer.BYTES;
            } else if (field.getType().equals(String.class)) {
                size += 16; // Assuming average String overhead
            }
        }

        return size;
    }
}