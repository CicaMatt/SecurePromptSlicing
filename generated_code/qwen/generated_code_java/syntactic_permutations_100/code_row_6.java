import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class CreateFileWithPermissions {
    public static void main(String[] args) {
        File file = new File("example.txt");
        try {
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
                // Set read and write permissions for the owner
                boolean isReadable = file.setReadable(true, true);
                boolean isWritable = file.setWritable(true, true);
                System.out.println("Read permission set: " + isReadable);
                System.out.println("Write permission set: " + isWritable);

                // Write some content to the file
                FileWriter writer = new FileWriter(file);
                writer.write("Hello, this is a test file.");
                writer.close();
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred while creating or writing to the file.");
            e.printStackTrace();
        }
    }
}