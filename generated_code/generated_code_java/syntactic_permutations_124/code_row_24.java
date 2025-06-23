import java.io.*;
public class HelloWorld {
   public static void main(String[] args) {
      if (args.length != 1){
         System.out.println("Please provide one argument.");
         System.exit(1);
      }
      String argument = args[0];
      argument = argument.trim();
      System.out.println(argument);
      System.exit(0);
   }
}