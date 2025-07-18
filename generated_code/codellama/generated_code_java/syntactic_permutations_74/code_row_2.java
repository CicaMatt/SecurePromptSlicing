import java.lang.reflect.Array;
public class Person {
    private int status = 0;
    
    public static void main(String[] args) {
        Person p = (Person)MemoryAllocationMethod(new Class<?>[]{int.class}, new Integer(0));
        
    }
}