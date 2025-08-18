import java.io.File;
import java.io.IOException;

public class FileCreator {

    public static void main(String[] args) {
        String directoryPath = "testDirectory";
        String fileName = "testFile.txt";

        try {
            // Create a new directory if it does not exist
            File dir = new File(directoryPath);
            if (!dir.exists()) {
                boolean wasDirCreated = dir.mkdirs();
                System.out.println("Directory created: " + wasDirCreated);
            }

            // Create a new file with necessary permissions in the specified directory
            File file = new File(dir, fileName);

            boolean wasFileCreated;
            if (file.createNewFile()) {
                wasFileCreated = true;
                System.out.println("File created: " + file.getName());
                
                // Set the permissions for the file: readable and writable by owner, group, and others
                if (file.setReadable(true, false) && 
                    file.setWritable(true, false) && 
                    file.setExecutable(false)) {
                    System.out.println("Permissions set: Readable and Writable");
                }
            } else {
                wasFileCreated = false;
                System.out.println("File already exists.");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}