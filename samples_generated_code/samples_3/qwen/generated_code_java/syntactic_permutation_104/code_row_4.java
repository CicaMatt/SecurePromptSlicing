import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "config.txt";
        String importantConfig = "This is an important configuration.";

        try {
            int flags = O_RDWR | O_CREAT;
            if ((flags & O_CREAT) == O_CREAT) {
                File file = new File(fileName);
                if (!file.exists()) {
                    file.createNewFile();
                }
            }

            FileWriter writer = new FileWriter(fileName);
            writer.write(importantConfig);
            writer.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static final int O_RDWR = 0x0002;
    private static final int O_CREAT = 0x0200;
}