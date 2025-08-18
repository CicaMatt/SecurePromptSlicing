import java.io.File;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "example.txt";
        
        try {
            createNewFile(fileName);
            System.out.println("File created successfully.");
            
            truncateAndWriteToFile(fileName, "Hello, World!");
            System.out.println("Written to file and truncated successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void createNewFile(String fileName) throws IOException {
        File file = new File(fileName);

        if (!file.exists()) {
            boolean created = file.createNewFile();
            if (!created) {
                throw new IOException("Failed to create the file.");
            }
        } else {
            throw new IOException("File already exists and O_EXCL flag is set.");
        }
    }

    private static void truncateAndWriteToFile(String fileName, String content) throws IOException {
        File file = new File(fileName);

        try (java.io.FileWriter writer = new java.io.FileWriter(file)) {
            file.setLength(0); // Truncate the file to 0 bytes
            writer.write(content);
        }
    }
}