import java.lang.reflect.Field;

class Main {
    private static final int MEMORY_SIZE = 1024; // Example size

    public static void main(String[] args) throws Exception {
        byte[] memory = new byte[MEMORY_SIZE];
        Person person = (Person) allocateMemory(Person.class, memory);
        
        Field statusField = Person.class.getDeclaredField("status");
        statusField.setAccessible(true);
        statusField.set(person, "John");

        System.out.println("Person Status: " + person.getStatus());
    }

    public static Object allocateMemory(Class<?> clazz, byte[] memory) throws Exception {
        if (memory == null || memory.length < clazz.getAnnotation(MemorySize.class).value()) {
            throw new IllegalArgumentException("Insufficient memory size");
        }
        
        int offset = 0;
        for (Field field : clazz.getDeclaredFields()) {
            field.setAccessible(true);
            Class<?> fieldType = field.getType();
            
            if (fieldType == byte.class || fieldType == Byte.class) {
                field.set(null, memory[offset++]);
            } else if (fieldType == short.class || fieldType == Short.class) {
                short value = (short) ((memory[offset] & 0xFF) << 8 | (memory[offset + 1] & 0xFF));
                field.set(null, value);
                offset += 2;
            } else if (fieldType == int.class || fieldType == Integer.class) {
                int value = (int) (((memory[offset] & 0xFF) << 24)
                        | ((memory[offset + 1] & 0xFF) << 16)
                        | ((memory[offset + 2] & 0xFF) << 8)
                        | (memory[offset + 3] & 0xFF));
                field.set(null, value);
                offset += 4;
            } else if (fieldType == long.class || fieldType == Long.class) {
                long value = (((long) (memory[offset] & 0xFF)) << 56
                        | ((long) (memory[offset + 1] & 0xFF) << 48)
                        | ((long) (memory[offset + 2] & 0xFF) << 40)
                        | ((long) (memory[offset + 3] & 0xFF) << 32)
                        | ((long) (memory[offset + 4] & 0xFF) << 24)
                        | ((long) (memory[offset + 5] & 0xFF) << 16)
                        | ((long) (memory[offset + 6] & 0xFF) << 8)
                        | ((long) (memory[offset + 7] & 0xFF)));
                field.set(null, value);
                offset += 8;
            } else if (fieldType == float.class || fieldType == Float.class) {
                int bits = (int) (((memory[offset] & 0xFF) << 24)
                        | ((memory[offset + 1] & 0xFF) << 16)
                        | ((memory[offset + 2] & 0xFF) << 8)
                        | (memory[offset + 3] & 0xFF));
                field.set(null, Float.intBitsToFloat(bits));
                offset += 4;
            } else if (fieldType == double.class || fieldType == Double.class) {
                long bits = (((long) (memory[offset] & 0xFF)) << 56
                        | ((long) (memory[offset + 1] & 0xFF) << 48)
                        | ((long) (memory[offset + 2] & 0xFF) << 40)
                        | ((long) (memory[offset + 3] & 0xFF) << 32)
                        | ((long) (memory[offset + 4] & 0xFF) << 24)
                        | ((long) (memory[offset + 5] & 0xFF) << 16)
                        | ((long) (memory[offset + 6] & 0xFF) << 8)
                        | ((long) (memory[offset + 7] & 0xFF)));
                field.set(null, Double.longBitsToDouble(bits));
                offset += 8;
            } else if (fieldType == boolean.class || fieldType == Boolean.class) {
                field.set(null, memory[offset++] != 0);
            } else if (fieldType.isPrimitive()) {
                throw new UnsupportedOperationException("Unsupported primitive type: " + fieldType);
            }
        }

        return clazz.getDeclaredConstructor().newInstance();
    }
}

class Person {
    private String status;

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}

@interface MemorySize {
    int value();
}