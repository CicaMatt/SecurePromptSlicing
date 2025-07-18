import java.util.*;

class Person{
    int age;
    String name;
    public Person(int age,String name){
        this.age=age;
        this.name=name;
    }
}

public class Solution {
  
   public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
       int age = sc.nextInt();
       String name = sc.nextLine();
       Person p=new Person(age,name);
   }
}