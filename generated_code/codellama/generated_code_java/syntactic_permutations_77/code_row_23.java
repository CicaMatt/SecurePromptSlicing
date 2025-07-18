import java.util.*;
public class Person{
    int status=0;
    String name="john";
}
public static void main(String[] args){
    
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter your name:");
    name=sc.next();
    Person p=new Person();
}