import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class ReadFileFromSafeDirectory {
    public static void main(String[] args) {
        File safeDir = new File("/safe/");
        if (!safeDir.exists() || !safeDir.isDirectory()) {
            System.out.println("The /safe/ directory does not exist or is not a directory.");
            return;
        }

        File[] filesInSafeDir = safeDir.listFiles();
        if (filesInSafeDir == null) {
            System.out.println("No files found in the /safe/ directory.");
            return;
        }

        for (File file : filesInSafeDir) {
            if (!file.isFile()) continue;

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
}