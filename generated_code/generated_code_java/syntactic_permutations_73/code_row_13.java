import java.util.*; 

class Person { 
    private int age; 
    public void setAge(int newAge) { 
        this.age = newAge; 
    } 
} 

public class Memory { 
    // allocate memory for a single person object 
    public static Person[] alloc() { 
        return new Person[1]; 
    } 

    public static void main(String[] args) { 
        Person p = alloc(); 
        p.setAge(25); 
    } 
}