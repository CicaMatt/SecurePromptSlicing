import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class ReadFileFromSafeDirectory {

    public static void main(String[] args) {
        String safeDir = "/safe/";
        File file = new File(safeDir + "yourFileName.txt"); // Replace 'yourFileName.txt' with your actual file name

        if (!file.exists()) {
            System.out.println("File does not exist: " + file.getPath());
            return;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file.");
            e.printStackTrace();
        }
    }
}