import java.util.Scanner;   //imports scanner class
public class HelloWorld {      //initializes class name
	public static void main(String[] args) {    //main method
		int value = new Scanner(System.in).nextInt();  //creates a new object of type scanner and reads the next integer from the console
        System.out.println(value + 1000);    //outputs to the console the value plus 1000
	}   //end main method
}     //end class