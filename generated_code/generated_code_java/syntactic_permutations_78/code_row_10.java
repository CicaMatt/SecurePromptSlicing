import java.lang.*;
import java.util.*;

public class MemoryAllocation {
    public static void main(String[] args) {
        Person p = (Person) allocate(sizeof(Person)); //allocating memory for a new person
        p.status = 0; //setting the status to 0
    }
}