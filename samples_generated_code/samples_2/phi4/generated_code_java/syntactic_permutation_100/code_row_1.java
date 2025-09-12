import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ImportantConfigCreator {

    public static void main(String[] args) {
        File configFile = new File("important_config");

        if (!configFile.exists()) {
            try {
                boolean created = configFile.createNewFile();
                if (created) {
                    System.out.println("Configuration file 'important_config' created successfully.");

                    // Set the necessary permissions: Read, Write and Execute for owner
                    boolean isWritable = configFile.setWritable(true);
                    boolean isReadable = configFile.setReadable(true);
                    boolean isExecutable = configFile.setExecutable(true);

                    if (isWritable && isReadable && isExecutable) {
                        System.out.println("Permissions set: Owner can read, write, and execute.");
                    } else {
                        System.err.println("Failed to set permissions for the file.");
                    }
                } else {
                    System.err.println("Failed to create configuration file. It may already exist.");
                }
            } catch (IOException e) {
                System.err.println("An error occurred while creating or setting permissions for the file: " + e.getMessage());
            }
        } else {
            System.out.println("Configuration file 'important_config' already exists.");
        }
    }
}