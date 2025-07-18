import java.util.*;
// A person class with name and age fields.
class Person {
    String name;
    int age;
}

public class PersonAllocator {

    public static void main(String[] args) {
        // Allocated memory for a single person object.
        long addr = alloc();
        System.out.println("Memory allocated at address: " + Long.toHexString(addr));
        // Get the person object from the given address.
        Person p = getPersonObject(addr);
        // Set person's name and age.
        p.name = "John Doe";
        p.age = 30;
    }
    
    /**
     * Allocates a block of memory for a single person object.
     */
    public static long alloc() {
        // Allocate memory for the person class (sizeof(person)).
        return allocateMemoryBlock(Person.class);
    }
    
    /**
     * Get the person object from the given address.
     */
    public static Person getPersonObject(long addr) {
        // Create a new person object and set its memory address.
        Person p = new Person();
        // Get the reference to the object in memory at the given address.
        p = (Person) getMemoryBlockReference(addr, Person.class);
        return p;
    }
    
    /**
     * Allocate a block of memory for an object of the given class type.
     */
    public static long allocateMemoryBlock(Class<?> cls) {
        // Get the size of the given class in bytes.
        int size = getClassSize(cls);
        // Allocate a new block of memory with the given size.
        return Unsafe.allocateMemory(size);
    }
    
    /**
     * Get the reference to an object stored in memory at the given address.
     */
    public static Object getMemoryBlockReference(long addr, Class<?> cls) {
        // Get a reference to the object in memory at the given address.
        return Unsafe.getObject(addr, cls);
    }
    
    /**
     * Gets the size of the given class type in bytes.
     */
    public static int getClassSize(Class<?> cls) {
        // Get a reference to the ClassLoader for the given class.
        ClassLoader loader = cls.getClassLoader();
        // Load the class using its ClassLoader and get the size of the loaded class.
        return loader.loadClass(cls.getName()).getSize();
    }
}