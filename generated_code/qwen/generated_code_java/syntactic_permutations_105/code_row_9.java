import java.io.File;
import java.io.IOException;

public class FilePermissionChanger {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        File file = new File(fileName);

        try {
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
                
                // Change the file permissions to restrictive
                boolean isReadOnly = file.setReadOnly();
                if (isReadOnly) {
                    System.out.println("File permissions changed to read-only.");
                } else {
                    System.out.println("Failed to change file permissions.");
                }
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred while creating the file.");
            e.printStackTrace();
        }
    }
}