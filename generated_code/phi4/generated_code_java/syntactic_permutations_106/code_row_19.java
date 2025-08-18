import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        String fileName = "secret_info.txt";

        try (FileWriter fileWriter = new FileWriter(fileName)) {
            fileWriter.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(fileName);

        if (file.exists()) {
            boolean success = file.setReadable(true, false); // Read permission for owner only
            boolean writeSuccess = file.setWritable(false, false); // No write permission for anyone
            boolean executeSuccess = file.setExecutable(false, false); // No execute permission

            System.out.println("File permissions changed successfully: " + fileName);
        } else {
            System.err.println("File not found: " + fileName);
        }

        System.out.println("The name of the file is: " + fileName);
    }
}