import java.util.*;
public class Person{
    public int status = 0;
}

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    
    public static void main(String[] args){
        System.out.println("Enter the number of person: ");
        int num = scanner.nextInt();
        
        Person p = (Person)malloc(sizeof(Person)*num);
        for(int i=0;i<num;i++){
            Person temp = p+i;
            temp.status = 0;
        }
    }
    
    public static malloc(int size){
        return new Person[size];
    }
}