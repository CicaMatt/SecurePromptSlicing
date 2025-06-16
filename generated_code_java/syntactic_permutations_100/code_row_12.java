import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Code {
    
   public static void main(String[] args) {
        try {
            File newTextFile = new File("important_config.txt");
            if (newTextFile.createNewFile()) {
                System.out.println("File created: " + newTextFile.getName());
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}