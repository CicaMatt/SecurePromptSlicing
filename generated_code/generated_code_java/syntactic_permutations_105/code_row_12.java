import java.io.*;
import java.util.*;

public class SecretFile {
   public static void main(String[] args) throws Exception {
      String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
      File file = new File("secret.txt");
      BufferedWriter writer = null;
      try{
         writer = new BufferedWriter(new FileWriter(file));
         writer.write(content);
      } finally {
         if (writer != null) {
            writer.close();
         }
      }
      Runtime rt = Runtime.getRuntime(); 
      Process prc = rt.exec("chmod 700 secret.txt");
   }
}