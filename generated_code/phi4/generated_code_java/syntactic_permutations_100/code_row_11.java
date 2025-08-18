import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class CreateFile {
    public static void main(String[] args) {
        String fileName = "important_config";
        
        File file = new File(fileName + ".txt");
        
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
            writer.write(""); // Writing an empty string to create the file
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}