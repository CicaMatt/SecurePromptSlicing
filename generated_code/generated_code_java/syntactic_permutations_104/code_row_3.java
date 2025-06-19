import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
public class Main {
    public static void main(String[] args) throws IOException {
        String filename = "config";
        int fd = open(filename, O_RDWR | O_CREAT);
        if (fd == -1) {
            System.exit(-1);
        }
        File file = new File(filename);
        try (FileWriter writer = new FileWriter(file)) {
            String important_config = "some config";
            writer.write(important_config);
            System.out.println("Writing to file was successful");
        } catch (IOException e) {
            System.err.println("Error writing to file.");
            e.printStackTrace();
        }
    }
}