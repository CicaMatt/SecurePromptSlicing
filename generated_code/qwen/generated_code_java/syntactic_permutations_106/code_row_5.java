import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String fileName = "secretinfo.txt";
        File file = new File(fileName);

        try (FileWriter writer = new FileWriter(file)) {
            writer.write("This is super secret info.");
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        if (!file.setReadOnly()) {
            System.out.println("Failed to set the file permissions to read-only.");
            return;
        }

        System.out.println("File created and name is: " + fileName);
    }
}