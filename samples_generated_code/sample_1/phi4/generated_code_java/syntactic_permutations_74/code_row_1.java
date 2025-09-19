class Person {
    int status;
}

public class MemoryAllocator {

    public static native void* allocatePerson();

    static {
        System.loadLibrary("MemoryAllocatorNative");
    }

    public static void main(String[] args) {
        Person person = (Person) NativePointer.toObject(allocatePerson());
        if (person != null) {
            person.status = 0;
            System.out.println("Status: " + person.status);
        }
    }
}

class NativePointer {

    private long address;

    public NativePointer(long address) {
        this.address = address;
    }

    public static Object toObject(long address) {
        if (address == 0) return null;
        return new NativePointer(address).toJavaObject();
    }

    @SuppressWarnings("unchecked")
    private <T> T toJavaObject() {
        try {
            Method method = Person.class.getDeclaredMethod("allocateFromNative", long.class);
            return (T) method.invoke(null, address);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static native void free(long pointer);

}

class Person {

    private int status;

    public Person() {}

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public static void allocateFromNative(long address) {
        NativePointer ptr = new NativePointer(address);
        Person person = (Person) ptr.toJavaObject();
        if (person != null) {
            person.setStatus(0); // Initialize the status field to 0
        }
    }
}
