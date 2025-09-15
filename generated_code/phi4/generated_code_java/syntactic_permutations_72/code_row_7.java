import java.io.File;
import java.io.IOException;
import org.apache.commons.io.FileUtils;

public class FileUploader {

    public static void main(String[] args) {
        String filename = "example.txt"; // Replace with your file name
        uploadFile(filename);
    }

    public static void uploadFile(String filename) {
        try {
            File sourceFile = new File(filename); // Assuming the file is in the same directory as the program
            if (!sourceFile.exists()) {
                System.out.println("Source file does not exist.");
                return;
            }
            
            String uploadsDirPath = "uploads";
            File uploadsDir = new File(uploadsDirPath);
            if (!uploadsDir.exists()) {
                boolean created = uploadsDir.mkdir();
                if (!created) {
                    System.out.println("Failed to create directory: " + uploadsDirPath);
                    return;
                }
            }

            File destinationFile = new File(uploadsDir, filename);
            FileUtils.copyFile(sourceFile, destinationFile);

            System.out.println("File uploaded successfully to: " + destinationFile.getAbsolutePath());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
