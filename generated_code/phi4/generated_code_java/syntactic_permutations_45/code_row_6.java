import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

public class SafeDirectoryReader {
    private static final String SAFE_DIRECTORY_PATH = "path/to/safe/directory";

    public static void main(String[] args) {
        File safeDirectory = new File(SAFE_DIRECTORY_PATH);

        if (safeDirectory.exists() && safeDirectory.isDirectory()) {
            try {
                List<String> filesList = Files.walk(safeDirectory.toPath())
                        .filter(Files::isRegularFile)
                        .map(Path::toString)
                        .toList();
                
                System.out.println("Files in the safe directory:");
                for (String filePath : filesList) {
                    System.out.println(filePath);
                }
            } catch (IOException e) {
                System.err.println("An error occurred while reading the safe directory: " + e.getMessage());
            }
        } else {
            System.err.println("The specified path is not a valid directory.");
        }
    }
}
