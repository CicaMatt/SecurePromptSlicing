import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileReadWriteExample {
    public static void main(String[] args) {
        String fileName = ".important_config";
        Path path = Paths.get(fileName);

        try {
            if (!Files.exists(path)) {
                Files.createFile(path);
            }

            FileWriter fileWriter = new FileWriter(fileName);
            fileWriter.write("important_config");
            fileWriter.close();
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}