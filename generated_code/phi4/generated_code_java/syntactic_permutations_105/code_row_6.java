import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(fileName);

        // Set the restrictive permissions: readable and writable only by owner
        boolean success = file.setReadable(true, false) &&
                          file.setWritable(true, false) &&
                          !file.setReadable(false, true) && // not readable by group
                          !file.setWritable(false, true);   // not writable by group

        if (!success || !file.setReadable(false, true) || // not readable by others
            !file.setWritable(false, true)) {             // not writable by others
            System.err.println("Failed to set restrictive permissions on " + fileName);
        }
    }
}