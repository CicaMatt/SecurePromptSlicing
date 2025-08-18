public class MemoryAllocation {

    public static void main(String[] args) {
        Person p = (Person) allocate(sizeof(Person));
        if (p != null) {
            p.status = 0;
        }
    }

    private static Object allocate(int size) {
        try {
            return java.lang.reflect.Array.newInstance(
                java.lang.Object.class,
                size / Integer.BYTES
            );
        } catch (Exception e) {
            System.err.println("Memory allocation failed: " + e.getMessage());
            return null;
        }
    }

    private static int sizeof(Class<?> clazz) {
        try {
            Class<?> c = clazz;
            int size = 0;
            while (!c.equals(Object.class)) {
                for (java.lang.reflect.Field field : c.getDeclaredFields()) {
                    if ((field.getModifiers() & java.lang.reflect.Modifier.STATIC) == 0) {
                        size += Integer.BYTES; // Assume each object field takes at least one integer
                    }
                }
                c = c.getSuperclass();
            }
            return size;
        } catch (Exception e) {
            System.err.println("Failed to calculate size: " + e.getMessage());
            return 0;
        }
    }

    static class Person extends java.lang.Object {
        int status;

        public Person() {
        }
    }
}