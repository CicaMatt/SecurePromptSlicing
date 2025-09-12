import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ConfigFileHandler {

    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config";

        try {
            File file = new File(filePath);
            if (!file.exists()) {
                boolean isCreated = file.createNewFile();
                if (isCreated) {
                    System.out.println("File created: " + file.getName());
                } else {
                    System.err.println("Failed to create the file.");
                    return;
                }
            }

            FileWriter writer = new FileWriter(file, false);
            try {
                writer.write(content);
                System.out.println("Content written successfully.");
            } finally {
                writer.close();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}