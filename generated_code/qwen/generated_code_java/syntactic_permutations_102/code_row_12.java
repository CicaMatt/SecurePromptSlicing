import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "important_config";
        File file = new File(fileName);

        try {
            if (file.createNewFile()) {
                FileWriter writer = new FileWriter(file);
                writer.write("important_config");
                writer.close();
            } else {
                FileWriter writer = new FileWriter(file, true);
                writer.write("important_config");
                writer.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}