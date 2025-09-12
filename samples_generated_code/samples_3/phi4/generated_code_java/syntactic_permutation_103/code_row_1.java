import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class OpenFileExample {

    public static void main(String[] args) {
        String filePath = "example.txt";

        try {
            // Check if the file exists and create it if it doesn't.
            File file = new File(filePath);
            boolean createdNew = file.createNewFile();

            if (!createdNew && !file.exists()) {
                throw new IOException("Failed to create a new file.");
            }

            // Open the file for writing only, truncating it first if it already exists.
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                System.out.println("File opened for writing. You can write data here.");
                // Example: Write some text to the file
                String content = "Hello, World!";
                fos.write(content.getBytes());
                System.out.println("Content written to file: " + content);
            }

        } catch (IOException e) {
            if (e.getMessage().contains("already exists")) {
                System.err.println("Failed to create the file because it already exists.");
            } else {
                e.printStackTrace();
            }
        }
    }
}