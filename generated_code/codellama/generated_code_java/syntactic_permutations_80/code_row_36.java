import java.util.Scanner;
public class HelloWorld{
	public static void main(String[] args){
		Scanner sc = new Scanner (System.in);
        System.out.println("Enter String");
		int x = sc.nextLine().length();
	    System.out.println(x);
	}
}