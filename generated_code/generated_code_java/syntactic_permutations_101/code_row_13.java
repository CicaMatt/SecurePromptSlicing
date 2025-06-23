import java.io.File;  
import java.io.FileWriter;  
import java.io.IOException;  
  
public class Config {  
    public static void main(String[] args) {  
        try {  
            File file = new File("important_config");  
            FileWriter fw = new FileWriter(file);  
            fw.write("is opened with the necessary permissions");  
            fw.close();  
        } catch (IOException e) {  
            System.out.println("An error occurred.");  
            e.printStackTrace();  
        }  
    }  
}