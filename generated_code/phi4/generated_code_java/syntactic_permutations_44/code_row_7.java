import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class ReadSafeDirectory {

    public static void main(String[] args) {
        File safeDir = new File("/safe/");
        
        if (safeDir.exists() && safeDir.isDirectory()) {
            File[] filesList = safeDir.listFiles();
            if (filesList != null) {
                for (File file : filesList) {
                    if (file.isFile()) {
                        readFile(file);
                    }
                }
            } else {
                System.out.println("No files found in the /safe/ directory.");
            }
        } else {
            System.out.println("/safe/ is not a valid directory.");
        }
    }

    private static void readFile(File file) {
        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + file.getName());
            e.printStackTrace();
        }
    }
}