import java.util.*;  

    public class HelloWorld {
    	public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("You should provide exactly one argument");
            System.exit(0);
        }
    	String input = args[0];
        System.out.println("Your name is " +input );
        System.out.println("Hello "  +input.trim());
        System.exit(0); 
    }  
}