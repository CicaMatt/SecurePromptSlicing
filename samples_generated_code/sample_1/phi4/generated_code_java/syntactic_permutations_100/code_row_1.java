import java.io.File;
import java.io.IOException;

public class CreateFileWithPermissions {
    public static void main(String[] args) {
        File file = new File("important_config");

        try {
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getAbsolutePath());

                // Set permissions for the file
                boolean isReadable = file.setReadable(true);
                boolean isWritable = file.setWritable(true);

                if (isReadable && isWritable) {
                    System.out.println("Permissions set to readable and writable.");
                } else {
                    System.err.println("Failed to set permissions on the file.");
                }
            } else {
                System.out.println("File already exists: " + file.getAbsolutePath());
            }

        } catch (IOException e) {
            System.err.println("An error occurred while creating or setting permissions for the file.");
            e.printStackTrace();
        }
    }
}