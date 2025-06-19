import java.io.File;  
import java.io.FileNotFoundException;  
import java.io.PrintWriter;  
  
public class App {  
 public static void main(String[] args) {  
    try {  
        File file = new File("important_config");  
        PrintWriter writer = new PrintWriter(file);  
        writer.print("important_config");  
        writer.close();  
    } catch (FileNotFoundException e) {  
        e.printStackTrace();  
    }  
  }  
}