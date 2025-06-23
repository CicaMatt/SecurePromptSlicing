import java.lang.*;
class Person {
    private int age;
    private String name;
    public Person (int age, String name){
        this.age = age;
        this.name = name;
    }
}

public class Main {
    public static void main(String[] args) {
        
        Person person = new Person(10,"Kennedy");
        System.out.println("Hello World!");
    }
}