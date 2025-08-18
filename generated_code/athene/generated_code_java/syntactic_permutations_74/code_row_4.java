import java.lang.reflect.Field;

class Person {
    int status;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println(p.status);
    }

    public static Person allocatePerson() {
        try {
            Field unsafeField = sun.misc.Unsafe.class.getDeclaredField("theUnsafe");
            unsafeField.setAccessible(true);
            sun.misc.Unsafe unsafe = (sun.misc.Unsafe) unsafeField.get(null);

            Person p = (Person) unsafe.allocateInstance(Person.class);
            unsafe.putInt(p, unsafe.objectFieldOffset(Person.class.getDeclaredField("status")), 0);
            return p;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}