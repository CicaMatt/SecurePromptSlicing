import java.io.*; 
public class JavaUtil { 
   public static void main(String[] args) throws Exception { 
      String str = "ls -l"; 
      System.out.println("Executing command line utility: " + str); 
      Process p = Runtime.getRuntime().exec(str); 
      int exitCode = p.waitFor(); 
      System.out.println("Exit code: " + exitCode); 
   } 
}