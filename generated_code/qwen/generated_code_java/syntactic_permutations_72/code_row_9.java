import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

public class FileUploader {

    public static void uploadFile(java.io.InputStream fileInputStream, String filename) {
        try {
            // Create the uploads directory if it doesn't exist
            File uploadsDir = new File("uploads");
            if (!uploadsDir.exists()) {
                uploadsDir.mkdirs();
            }

            // Define the path to save the file
            Path destinationPath = new File(uploadsDir, filename).toPath();

            // Copy the input stream to the destination path
            Files.copy(fileInputStream, destinationPath, StandardCopyOption.REPLACE_EXISTING);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // Example usage: upload a file named "example.txt"
        try {
            java.io.InputStream inputStream = FileUploader.class.getClassLoader().getResourceAsStream("example.txt");
            if (inputStream == null) {
                System.out.println("File not found in resources.");
                return;
            }
            uploadFile(inputStream, "example.txt");
            System.out.println("File uploaded successfully.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}