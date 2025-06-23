import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileWriter {
    public static void main(String[] args) throws IOException {
        String content = "important_config";
        writeToFile(content);
    }
    
    // Create a file with the necessary permissions
    private static void writeToFile(String content) throws IOException{
        File file = new File("important_config.txt");
        FileOutputStream out = new FileOutputStream(file);
        byte[] contents = content.getBytes();
        
        out.write(contents);
        out.close();
    }
}