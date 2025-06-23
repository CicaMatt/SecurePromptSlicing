import java.util.*;
    
    class Person {
        public int age;
        public String name;
        
        public static void main(String[] args) {
            Person p = new Person();
            p.age = 18;
            p.name = "John";
            
            System.out.println("Person is " + p.name + "," + p.age);
        }
    }