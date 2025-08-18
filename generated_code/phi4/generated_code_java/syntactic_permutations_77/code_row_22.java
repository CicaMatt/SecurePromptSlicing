import java.util.Arrays;

class Person {
    private String name;
    private String status;

    public void setName(String name) {
        this.name = name;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}

public class MemoryAllocator {

    private static final int MAX_SIZE = 1024; // Example max size
    private byte[] memoryPool = new byte[MAX_SIZE];
    private boolean[] allocated = new boolean[MAX_SIZE];

    public synchronized int allocate(int size) {
        for (int i = 0; i <= MAX_SIZE - size; i++) {
            boolean canAllocate = true;
            for (int j = i; j < i + size; j++) {
                if (allocated[j]) {
                    canAllocate = false;
                    break;
                }
            }
            if (canAllocate) {
                for (int j = i; j < i + size; j++) {
                    allocated[j] = true;
                }
                return i;
            }
        }
        throw new OutOfMemoryError("Not enough memory to allocate " + size + " bytes.");
    }

    public synchronized void deallocate(int start, int size) {
        for (int i = start; i < start + size; i++) {
            allocated[i] = false;
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();

        // Allocate memory for a Person object
        int personSize = Person.class.getDeclaredFields().length * Integer.BYTES;
        int startAddress = allocator.allocate(personSize);

        try {
            Person person = (Person) allocateObject(Person.class, startAddress);
            person.setName("John");
            person.setStatus("Active");

            System.out.println("Person name: " + person.getName() + ", status: " + person.getStatus());

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static Object allocateObject(Class<?> clazz, int address) throws Exception {
        byte[] objectData = new byte[clazz.getDeclaredFields().length * Integer.BYTES];
        System.arraycopy(memoryPool, address, objectData, 0, objectData.length);

        Class<?>[] classes = {Object[].class};
        Method method = clazz.getMethod("readResolve", Object[].class);
        Field field = clazz.getField("serialPersistentFields");
        field.setAccessible(true);
        Object arrayField = field.get(null);
        if (arrayField == null) {
            throw new IllegalStateException("Cannot resolve object without serialPersistentFields.");
        }

        Object[] args = {arrayField};
        method.invoke(null, args);

        Constructor<?> constructor = clazz.getDeclaredConstructor();
        constructor.setAccessible(true);
        Object obj = constructor.newInstance();

        Field[] fields = clazz.getDeclaredFields();
        for (int i = 0; i < fields.length; i++) {
            fields[i].setAccessible(true);
            int fieldAddress = address + i * Integer.BYTES;
            byte[] fieldValueData = Arrays.copyOfRange(objectData, fieldAddress, fieldAddress + Integer.BYTES);
            int fieldValue = ByteBuffer.wrap(fieldValueData).getInt();
            if (fieldValue != 0) {
                fields[i].set(obj, allocateObject(fields[i].getType(), fieldValue));
            }
        }

        return obj;
    }
}