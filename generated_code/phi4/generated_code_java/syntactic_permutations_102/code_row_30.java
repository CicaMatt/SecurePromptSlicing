import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;

public class ConfigFileManager {
    private static final String FILE_NAME = "important_config";

    public void openAndWrite(String content) throws IOException {
        File file = new File(FILE_NAME);
        
        // Create the file if it does not exist with specified permissions
        boolean created = file.createNewFile();
        if (created || file.exists()) {
            try (RandomAccessFile randomAccessFile = new RandomAccessFile(file, "rw")) {
                randomAccessFile.writeBytes(content);
            }
        } else {
            throw new IOException("Failed to create the file.");
        }
    }

    public static void main(String[] args) {
        ConfigFileManager manager = new ConfigFileManager();
        try {
            manager.openAndWrite("Sample configuration data.\n");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}