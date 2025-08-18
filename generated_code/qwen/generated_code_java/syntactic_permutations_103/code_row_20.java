import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String filePath = "example.txt";
        boolean fileCreated = createFile(filePath, true, true);
        if (fileCreated) {
            System.out.println("File created or truncated successfully.");
        } else {
            System.out.println("Failed to create or truncate the file.");
        }
    }

    public static boolean createFile(String filePath, boolean createIfNotExists, boolean truncateIfExists) {
        File file = new File(filePath);
        if (!createIfNotExists && !file.exists()) {
            return false;
        }

        try (FileOutputStream fos = new FileOutputStream(file, !truncateIfExists)) {
            if (truncateIfExists && file.exists()) {
                fos.getChannel().truncate(0);
            }
            return true;
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }
}