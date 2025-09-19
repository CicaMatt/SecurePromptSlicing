import java.lang.reflect.Field;
import java.util.ArrayList;

public class MemoryAllocator {

    private byte[] memoryPool;
    private int pointer = 0;
    
    public MemoryAllocator(int size) {
        this.memoryPool = new byte[size];
    }

    @SuppressWarnings("unchecked")
    public <T> T allocate(Class<T> clazz) {
        int size = calculateSize(clazz);
        
        if (pointer + size > memoryPool.length) {
            throw new OutOfMemoryError("Insufficient memory in pool");
        }
        
        T instance;
        try {
            // Using reflection to create a new instance of the class
            instance = clazz.getDeclaredConstructor().newInstance();
            
            Field[] fields = clazz.getDeclaredFields();
            for (Field field : fields) {
                field.setAccessible(true);
                
                if (field.getType().isPrimitive()) {
                    int primitiveSize = java.lang.reflect.TypeUtils.primitiveToWrapperType(field.getType()).getClass().getDeclaredConstructor().newInstance().getClass().getSimpleName().length() * 4;
                    
                    byte[] fieldValueBytes = new byte[primitiveSize];
                    System.arraycopy(memoryPool, pointer, fieldValueBytes, 0, fieldValueBytes.length);
                    field.set(instance, convertPrimitiveByteArray(fieldValueBytes, field.getType()));
                } else {
                    T nestedInstance = allocate((Class<T>)field.getType());
                    field.set(instance, nestedInstance);
                }
                
                pointer += primitiveSize;
            }
        } catch (Exception e) {
            throw new RuntimeException("Allocation error", e);
        }
        
        return instance;
    }

    private int calculateSize(Class<?> clazz) {
        Field[] fields = clazz.getDeclaredFields();
        int size = 0;
        for (Field field : fields) {
            if (field.getType().isPrimitive()) {
                size += java.lang.reflect.TypeUtils.primitiveToWrapperType(field.getType()).getClass().getDeclaredConstructor().newInstance().getClass().getSimpleName().length() * 4;
            } else {
                size += calculateSize((Class<?>)field.getType());
            }
        }
        return size;
    }

    private Object convertPrimitiveByteArray(byte[] bytes, Class<?> type) {
        if (type.equals(int.class)) {
            return byteArrayToInt(bytes);
        }
        // Add other primitive conversions as needed
        throw new IllegalArgumentException("Unsupported primitive type");
    }

    private int byteArrayToInt(byte[] b) {
        return ((b[3] & 0xFF) << 24) | ((b[2] & 0xFF) << 16) | ((b[1] & 0xFF) << 8) | (b[0] & 0xFF);
    }

    public static class Person {
        int age;
        String name;

        public Person() {}

        public void setAge(int age) {
            this.age = age;
        }

        public void setName(String name) {
            this.name = name;
        }
        
        @Override
        public String toString() {
            return "Person{name='" + name + "', age=" + age + "}";
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024);
        Person person = allocator.allocate(Person.class);
        System.out.println(person); // Output will be a default created instance
    }
}