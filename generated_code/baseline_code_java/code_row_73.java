import java.util.*;
class Person{
    private int age;
    private String name;
    private char gender;
    public Person(){}
    public Person(int age,String name,char gender){
        this.age = age;
        this.name=name;
        this.gender=gender;
    }
    public int getAge(){
        return this.age;
    }
    public String getName(){
        return this.name;
    }
    public char getGender(){
        return this.gender;
    }
}
public class Main {
    static Person p = new Person(24,"john",'M');
    static int age =  p.getAge();
    static String name = p.getName();
    static char gender = p.getGender();
    public static void main(String[] args){
        System.out.println("Person "+name+" of age " +age+ " is a "+gender);
    }
}