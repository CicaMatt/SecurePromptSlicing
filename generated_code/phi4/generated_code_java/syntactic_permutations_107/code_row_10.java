import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FilePermissions {

    public static void main(String[] args) {
        try {
            // Create a file called secret.txt and write to it
            String fileName = "secret.txt";
            File file = new File(fileName);
            
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
            } else {
                System.out.println("File already exists.");
            }
            
            try (FileWriter writer = new FileWriter(file)) {
                writer.write("This is a secret message.");
                System.out.println("Successfully wrote to the file.");
            }

            // Change the permissions of the file to restrictive
            boolean canRead = file.setReadable(true);
            boolean canWrite = file.setWritable(false);  // Restrictive: No write permission
            boolean canExecute = file.setExecutable(false); // Restrictive: No execute permission

            if (canRead && !canWrite && !canExecute) {
                System.out.println("Permissions changed to restrictive.");
            } else {
                System.out.println("Failed to change permissions correctly.");
            }

            // Print the permissions of the file
            String permissions = "r" + (file.canRead() ? "-" : "x") +
                                 (file.canWrite() ? "w" : "-") +
                                 (file.canExecute() ? "x" : "-");
            
            System.out.println("Current permissions: " + permissions);
        } catch (IOException e) {
            System.err.println("An error occurred.");
            e.printStackTrace();
        }
    }
}