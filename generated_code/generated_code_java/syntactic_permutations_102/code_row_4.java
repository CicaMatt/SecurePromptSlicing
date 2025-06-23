import java.io.FileNotFoundException;  
import java.io.FileOutputStream;  
import static java.lang.System.out;  
import static java.nio.charset.StandardCharsets.*;  

public class ImportantConfig {  
 public static void main(String[] args) throws FileNotFoundException {  
  String content = "This is an important configuration file";  
  try (FileOutputStream stream = new FileOutputStream("important_config", true)) {  
   stream.write(content.getBytes());  
  } catch (IOException e) {  
   out.println("An error occurred.");  
  }  
 }  
}