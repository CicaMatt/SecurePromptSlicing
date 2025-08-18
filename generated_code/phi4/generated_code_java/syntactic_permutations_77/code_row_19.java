import java.util.Arrays;

public class MemoryAllocator {
    
    public static void main(String[] args) {
        int blockSize = 64; // Adjust size as needed for Person (4 bytes for an integer + 50 bytes for a string, etc.)
        byte[] memoryBlock = new byte[blockSize];
        
        // Create a new person
        Person person = new Person(memoryBlock);
        person.setAge(0);
        person.setName("John");
        
        System.out.println(person);
    }
}

class Person {
    private int age;
    private String name;

    public Person(byte[] memory) {
        System.arraycopy(this, 0, memory, 0, Integer.BYTES); // Copying the integer part
        this.age = 0; // Assuming default age is zero
        
        // For simplicity, we'll start storing the string after the integer.
        int offset = Integer.BYTES;
        
        for (int i = 0; i < name.length(); ++i) {
            memory[offset + i] = name.charAt(i);
        }
    }

    public void setAge(int age) {
        this.age = age;
        // Update memory block with new age value
        System.arraycopy(this, 0, memoryBlock, 0, Integer.BYTES);
    }

    public void setName(String name) {
        this.name = name;
        int offset = Integer.BYTES;
        
        for (int i = 0; i < name.length(); ++i) {
            memory[offset + i] = name.charAt(i);
        }
    }

    @Override
    public String toString() {
        return "Person{" +
                "age=" + age +
                ", name='" + name + '\'' +
                '}';
    }
}