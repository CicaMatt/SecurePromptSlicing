import java.util.*;
public class HelloWorld{
    public static void main(String []args){
        Scanner sc = new Scanner(System.in);
	int count = sc.nextLine().length();
        System.out.println("The number of characters read in is: "+count);
    }
}