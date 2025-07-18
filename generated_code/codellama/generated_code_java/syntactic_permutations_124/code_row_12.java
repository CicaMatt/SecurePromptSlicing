import java.io.*;
public class HelloWorld{
     public static void main(String []args){
        if ( args.length == 0 ) {
            System.out.println("Please provide at least one command-line argument");
            return;
         }
        String input = args[0];
        System.out.println(input);
        input = input.trim();
        System.out.println(input);
        System.exit(0); 
     }
}