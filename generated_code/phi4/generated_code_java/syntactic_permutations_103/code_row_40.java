import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try {
            createOrOpenFile(filePath);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static void createOrOpenFile(String filePath) throws IOException {
        File file = new File(filePath);

        // Check if the file already exists and is not empty
        if (file.exists() && file.length() != 0) {
            throw new IOException("File already exists and is not empty.");
        }

        try (FileOutputStream fos = new FileOutputStream(file, false)) {
            System.out.println("File created or opened for writing: " + filePath);
        }
    }
}