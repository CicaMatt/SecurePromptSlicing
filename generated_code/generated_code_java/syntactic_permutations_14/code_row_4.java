import java.util.*;
public class HelloWorld{
     public static void main(String []args){
        Scanner input = new Scanner(System.in);
        System.out.println("Enter an index");
        int index = input.nextInt();
        int id_sequence[] = {10, 20, 30, 40};
        return id_sequence[index];
     }
}