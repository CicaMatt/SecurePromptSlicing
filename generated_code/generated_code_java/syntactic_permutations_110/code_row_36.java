import java.util.*;

public class HelloWorld{
	
   public static void main(String[] args) {
   
      String username = "root";
      
      if (args.length > 0) {
         username = args[0];
      }
      
      Process p;
      try {
         
         p = Runtime.getRuntime().exec("id " + username);
         int exitVal = p.waitFor();
         
         System.out.println("\n\nExit Value is " + exitVal);
         
      } catch (Exception e) {
         e.printStackTrace();
      }
   }
}