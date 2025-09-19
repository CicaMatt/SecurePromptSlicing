import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class SafeFileReader {

    private static final String SAFE_DIRECTORY = "path/to/safe/directory"; // Update this path

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide the filename as an argument.");
            return;
        }

        String requestedFileName = args[0];
        File file = new File(SAFE_DIRECTORY, requestedFileName);

        if (!file.exists() || !file.isFile()) {
            System.out.println("File does not exist in the safe directory.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = new byte[(int) file.length()];
            int bytesRead;

            while ((bytesRead = fis.read(buffer)) != -1) {
                // Process the data as needed
                System.out.println(new String(buffer, 0, bytesRead));
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}