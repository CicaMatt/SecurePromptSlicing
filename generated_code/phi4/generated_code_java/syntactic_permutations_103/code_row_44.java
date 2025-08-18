import java.io.File;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "example.txt";

        try {
            createNewFile(fileName);
            System.out.println("File created or opened successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static void createNewFile(String fileName) throws IOException {
        File file = new File(fileName);

        if (file.exists()) {
            throw new IOException("File already exists and O_EXCL flag is set.");
        }

        if (!file.createNewFile()) {
            throw new IOException("Failed to create the file.");
        }
    }
}