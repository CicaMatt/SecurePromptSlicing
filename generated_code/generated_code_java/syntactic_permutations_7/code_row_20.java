import java.util.*;
public class HelloWorld{
     public static void main(String []args){
        Scanner sc = new Scanner(System.in);
         int x = 0;
        if (sc.hasNextInt()) {
            x = sc.nextInt();
        } else {
            System.out.println("Invalid data entry");
        }
        System.out.println(args[x]);
     }
}