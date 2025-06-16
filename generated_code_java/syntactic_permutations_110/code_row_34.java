import java.util.*;

public class CommandReturn {
   public static void main(String[] args) {
       String username = args[0];
       try {
           Process proc = Runtime.getRuntime().exec("id " + username);
           int exitVal = proc.waitFor();
           System.out.println("\n\nExit Value is " + exitVal);
       } catch (Throwable t) {
           t.printStackTrace();
       }
   }
}