import java.util.Scanner;
public class HelloWorld {
   public static void main(String[] args) {
      if (args.length != 1){
          System.out.println("Please provide one and only one argument");
          System.exit(0);
      }
      String arg = args[0];
      arg=arg.trim();
      System.out.println(arg);
   }
}