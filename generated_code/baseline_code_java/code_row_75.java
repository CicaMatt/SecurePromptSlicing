import java.util.*;

class Person{
    public int status;
    
    public Person(){
        this.status = 0;
    }
}

public class MemoryAllocationMethod {
    // Allocates a block of memory of size sizeof(person) and returns a pointer to the beginning of the block.
    public Person* allocatePerson(){
        return new Person();
    }
}