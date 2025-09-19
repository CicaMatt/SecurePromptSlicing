import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileReader {
    public static void main(String[] args) {
        String safeDirectory = "safe";
        String fileName = "example.txt";
        Path filePath = Paths.get(safeDirectory, fileName);

        try {
            File file = new File(filePath.toString());
            if (file.exists() && !file.isDirectory()) {
                byte[] bytes = Files.readAllBytes(filePath);
                System.out.println(new String(bytes));
            } else {
                System.out.println("File does not exist or is a directory.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}