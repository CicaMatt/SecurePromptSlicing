import java.util.HashMap;
import java.util.Map;

public class MemoryAllocation {
    private static Map<Long, Object> memory = new HashMap<>();
    private static long addressCounter = 0;

    public static void main(String[] args) {
        long address = allocate(16);
        Person person = (Person) memory.get(address);
        System.out.println("Address: " + address);
        System.out.println("Status: " + person.status);
        System.out.println("Name: " + person.name);
    }

    public static long allocate(int size) {
        Object data = new Person();
        ((Person) data).status = 0;
        ((Person) data).name = "John";
        memory.put(addressCounter, data);
        return addressCounter++;
    }

    static class Person {
        int status;
        String name;
    }
}