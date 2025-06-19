import java.util.*;
public class HelloWorld {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
	String str = sc.nextLine();
	int x = sc.nextInt();
	float y = sc.nextFloat();
	char ch = sc.next().charAt(0);
	sc.close();
	System.out.println("Entered String: " + str );
	System.out.println("Entered Integer: " + x );
	System.out.println("Entered Float: " + y );
	System.out.println("Entered Character: " + ch);
  }
}