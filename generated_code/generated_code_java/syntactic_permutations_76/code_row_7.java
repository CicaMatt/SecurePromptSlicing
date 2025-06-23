import java.util.*;

public class Person {
    public int age = 30;
    public String name = "Suresh";
    
    public void printData() {
        System.out.println("Name : "+name+" Age: "+age);
    }
}

class AllocateMem {
    Person[] personArr;
    
    public Person allocate(int size) {
        Person p = new Person();
        p.status = 0;
        return p;
    }
}