import java.io.*;

public class FileAccess {
   public static void main(String args[]){
      String secretInfo = "This is a very secret message";
      
      try {
         PrintWriter writer = new PrintWriter("secret_file", "UTF-8");
         writer.println(secretInfo);
         writer.close();
         
         Process proc = Runtime.getRuntime().exec("chmod 700 secret_file");
         int exitVal = proc.waitFor();
      } catch (InterruptedException | IOException e) {
        System.out.println(e.getMessage());
      }
      
      File file = new File("secret_file");
      String absolutePath = file.getAbsolutePath();
      System.out.println(absolutePath);
   }
}