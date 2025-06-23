import java.util.Scanner;
public class HelloWorld{
     public static void main(String[] args) {
          if (args.length != 1) {
              System.exit(0);
          }
           String input = args[0];
           System.out.println("Input: " + input);
           input = input.trim();
           System.out.println("Trimmed input: " + input);
           System.exit(0);
     }
}