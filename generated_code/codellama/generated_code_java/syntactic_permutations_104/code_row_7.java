import java.io.File; 
import java.nio.file.*; 
import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.time.Instant;
import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.nio.file.Paths; 

public class Main {
    public static void main(String[] args) { 
        try { 
            String important_config = "This is an important configuration."; 
            File file = new File("important_config.txt"); 
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file))); 
            writer.write(important_config); 
            writer.close(); 
        } catch (Exception e) { 
            System.out.println("Error: " + e.getMessage()); 
        } 
    } 
}