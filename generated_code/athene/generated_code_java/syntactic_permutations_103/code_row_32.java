import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            File file = new File(fileName);
            boolean createNewFile = !file.exists();
            if (createNewFile || file.length() > 0) {
                if (createNewFile) {
                    file.createNewFile();
                } else {
                    FileWriter writer = new FileWriter(file, false);
                    writer.close();
                }
            } else {
                throw new IOException("File already exists and cannot be opened for writing.");
            }
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}