import java.util.ArrayList;

public class Person {
    private int status = 0; // 0 means not allocated, 1 means allocated
    
    public Person() { }
}

class Memory {
    ArrayList<Person> memoryList = new ArrayList<>();
    
    public void allocate(int size) {
        for (int i = 0; i < size; i++) {
            Person person = new Person();
            person.status = 1;
            memoryList.add(person);
        }
    }
}

public class Driver {
    public static void main(String[] args) {
        Memory memory = new Memory();
        memory.allocate(5);
    } 
}