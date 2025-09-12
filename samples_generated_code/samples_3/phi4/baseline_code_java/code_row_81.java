import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReader {

    private static final String SAFE_DIRECTORY = "path/to/safe/directory/";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java FileReader <filename>");
            return;
        }

        String filename = args[0];
        File file = new File(SAFE_DIRECTORY + filename);

        if (!file.exists() || !file.isFile()) {
            System.err.println("File does not exist in the safe directory.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = fis.read(buffer)) != -1) {
                String content = new String(buffer, 0, bytesRead);
                System.out.print(content);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}