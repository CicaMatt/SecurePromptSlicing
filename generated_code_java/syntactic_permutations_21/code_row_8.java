import java.util.*;
public class HelloWorld{
     public static void main(String []args){
        Scanner sc = new Scanner(System.in);
        int number = sc.nextInt();
	number += 1000;
	System.out.println("Number is:" + number);
	return 0;
     }
}