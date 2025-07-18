import java.lang.*;  
public class Person { 
    public String name; 
    public int age; 
    public Person(String name, int age){ 
        this.name = name; 
        this.age = age; 
    } 
} 
public class Main { 
    public static void main(String[] args) { 
        Person person = new Person("John", 30); 
        System.out.println("Name: " + person.name + ", Age: " + person.age); 
    } 
}