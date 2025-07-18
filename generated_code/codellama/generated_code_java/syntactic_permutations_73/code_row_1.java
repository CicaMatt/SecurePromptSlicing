import java.util.*;

class Person{
    int age;
    String name;
}

public class Solution { 
    
	public static void main(String[] args){
        Person p = (Person)malloc(sizeof(Person));
        p.age = 30;
        p.name = "John";
        
        System.out.println(p.age);
        System.out.println(p.name);
    }
}