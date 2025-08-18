import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class ReadFileFromSafeDirectory {
    public static void main(String[] args) {
        File safeDir = new File("/safe/");
        File fileToRead = null;
        
        if (safeDir.isDirectory()) {
            // List all files in the directory and read the first one
            String[] fileList = safeDir.list();
            if (fileList != null && fileList.length > 0) {
                fileToRead = new File(safeDir, fileList[0]);
                
                try (BufferedReader br = new BufferedReader(new FileReader(fileToRead))) {
                    String line;
                    while ((line = br.readLine()) != null) {
                        System.out.println(line);
                    }
                } catch (IOException e) {
                    System.err.println("Error reading file: " + e.getMessage());
                }
            } else {
                System.out.println("No files found in /safe/ directory.");
            }
        } else {
            System.out.println("/safe/ is not a directory or does not exist.");
        }
    }
}