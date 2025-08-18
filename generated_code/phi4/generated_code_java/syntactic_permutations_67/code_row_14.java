import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ImageStorage {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java ImageStorage <input-image-file> <output-directory>");
            return;
        }

        String inputImagePath = args[0];
        String outputDirectoryPath = args[1];

        File inputFile = new File(inputImagePath);
        File outputFileDir = new File(outputDirectoryPath);

        if (!inputFile.exists()) {
            System.out.println("Input file does not exist.");
            return;
        }

        if (!outputFileDir.exists() && !outputFileDir.mkdirs()) {
            System.out.println("Failed to create output directory.");
            return;
        }

        String fileName = inputFile.getName();
        File outputFile = new File(outputDirectoryPath, fileName);

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = fis.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }

            System.out.println("Image file has been copied to: " + outputFile.getAbsolutePath());

        } catch (IOException e) {
            System.err.println("An error occurred during file operations: " + e.getMessage());
        }
    }
}