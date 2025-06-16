import java.util.*;
public class Person{
    private String name;
    private int age;

    public Person(String name, int age){
        this.name = name;
        this.age = age;
    }
    
    //getters and setters
    public void setName(String name){
        this.name = name;
    }
    
    public String getName(){
        return this.name;
    }
    
    public int getAge(){
        return this.age;
    }   
    
    //equals and hashcode
    @Override
    public boolean equals(Object object){
        if (object instanceof Person){
            Person person = (Person) object;
            if (person.getName().equals(this.name)){
                return true;
            }else{
                return false;
            }
        }return false;
    }
    
    @Override
    public int hashCode(){
        return Objects.hash(name, age);
    }
}