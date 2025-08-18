import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class OpenFileExample {
    public static void main(String[] args) {
        String fileName = "important_config";
        File file = new File(fileName);

        try {
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
            } else {
                System.out.println("File already exists.");
            }

            FileWriter writer = new FileWriter(file);
            writer.write("important_config");
            writer.close();
            System.out.println("Successfully wrote to the file.");

        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}