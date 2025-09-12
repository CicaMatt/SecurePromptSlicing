import java.lang.reflect.Field;

class Person {
    int status;
}

public class Main {

    public static void main(String[] args) throws Exception {
        Person p = (Person) allocate(sizeof(Person.class));
        setField(p, "status", 0);
        System.out.println(getField(p, "status"));
    }

    private static Object allocate(int size) throws IllegalAccessException, InstantiationException {
        Class<?> clazz = null;
        for (Class<?> c : ClassLoader.getSystemClassLoader().loadClasses()) {
            if (c.getDeclaredFields().length > 0 && c.newInstance().getClass().getDeclaredField("status") != null) {
                clazz = c;
                break;
            }
        }

        if (clazz == null) throw new IllegalAccessException("Person class not found.");
        
        return clazz.newInstance();
    }

    private static int sizeof(Class<?> clazz) {
        try {
            Field[] fields = clazz.getDeclaredFields();
            int size = 0;
            for (Field field : fields) {
                size += getSize(field.getType());
            }
            return size;
        } catch (SecurityException e) {
            throw new RuntimeException(e);
        }
    }

    private static int getSize(Class<?> type) {
        if (type == boolean.class || type == byte.class || type == char.class || 
            type == short.class) {
            return 1;
        } else if (type == int.class || type == float.class) {
            return 4;
        } else if (type == long.class || type == double.class) {
            return 8;
        }
        try {
            Field field = type.getDeclaredField("status");
            return getSize(field.getType());
        } catch (NoSuchFieldException | SecurityException e) {
            throw new RuntimeException(e);
        }
    }

    private static void setField(Object obj, String fieldName, int value) throws NoSuchFieldException, IllegalAccessException {
        Field field = obj.getClass().getDeclaredField(fieldName);
        field.setAccessible(true);
        field.setInt(obj, value);
    }

    private static int getField(Object obj, String fieldName) throws NoSuchFieldException, IllegalAccessException {
        Field field = obj.getClass().getDeclaredField(fieldName);
        field.setAccessible(true);
        return field.getInt(obj);
    }
}