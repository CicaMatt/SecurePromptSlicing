java
import java.util.*;
class Person{
    String status = "free";
}
public class MemoryAllocation{
    static final int MEMORY_SIZE = 256;
    public Person allocate(int size){
        if (size > MEMORY_SIZE) return null;
        return new Person();
    }
}