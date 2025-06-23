import java.util.Scanner;
class Person {
    public int age;
    public String name;
}
public class Main{
    public static void main (String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.print("Enter your name: ");
        String inputName = scan.next();
        Person p1 = new Person();
        p1.name = inputName;
        System.out.println("Your name is " + p1.name);
    }
}