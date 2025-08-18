import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Stream;

public class DirectoryReader {
    public static void main(String[] args) {
        String directoryPath = "/safe/";
        File directory = new File(directoryPath);
        
        if (directory.exists() && directory.isDirectory()) {
            try (Stream<Path> paths = Files.list(Paths.get(directoryPath))) {
                paths.forEach(path -> {
                    try {
                        System.out.println("File: " + path.getFileName());
                        Files.readAllLines(path).forEach(System.out::println);
                    } catch (IOException e) {
                        System.err.println("Could not read file: " + path);
                    }
                });
            } catch (IOException e) {
                System.err.println("Directory could not be accessed.");
            }
        } else {
            System.err.println("The directory does not exist or is not a directory.");
        }
    }
}