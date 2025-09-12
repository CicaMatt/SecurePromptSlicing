import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            openFile(fileName);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static void openFile(String fileName) throws IOException {
        File file = new File(fileName);

        if (file.exists()) {
            throw new FileNotFoundException("File already exists, cannot create a new one with O_EXCL flag.");
        }

        // Open the file for writing only and truncate it to 0 bytes
        try (FileOutputStream fos = new FileOutputStream(file, false)) {
            System.out.println("File created and opened successfully.");
        }
    }
}