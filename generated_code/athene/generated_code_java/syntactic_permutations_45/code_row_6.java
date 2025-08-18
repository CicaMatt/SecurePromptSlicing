import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Stream;

public class SafeDirectoryReader {
    public static void main(String[] args) {
        String safeDirPath = "safe_directory";
        File dir = new File(safeDirPath);
        
        if (!dir.exists() || !dir.isDirectory()) {
            System.out.println("The specified path is not a directory or does not exist.");
            return;
        }

        try (Stream<Path> paths = Files.list(Paths.get(safeDirPath))) {
            paths.forEach(path -> {
                try {
                    System.out.println("File: " + path.getFileName() + ", Size: " + Files.size(path) + " bytes");
                } catch (IOException e) {
                    System.err.println("Error reading file size for " + path);
                }
            });
        } catch (IOException e) {
            System.err.println("Error reading directory: " + safeDirPath);
        }
    }
}