import java.util.*; 
public class CommandLineOffset { 
   public static void main(String[] args) { 
      int offset = 5;
      int value = Integer.parseInt(args[0]);
      System.out.println("The new value is " + (value + offset)); 
   } 
}