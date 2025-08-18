import java.io.*;

public class ImportantConfigFile {
    public static void main(String[] args) throws IOException {
        String filename = "important_config";
        File file = new File(filename);
        
        // Open or create the file with appropriate permissions (simulated here using Java's FileWriter)
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file, true))) {
            // Write string to the file
            writer.write("important_config");
            
            System.out.println("File written successfully.");
        }
    }
}