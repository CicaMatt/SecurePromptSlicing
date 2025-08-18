import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileWriteAndPerm {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        File file = new File("output.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(content);
            
            if (!file.setWritable(false, false)) {
                System.out.println("Failed to set write permission.");
            }
            if (!file.setReadable(false, false)) {
                System.out.println("Failed to set read permission.");
            }
            if (!file.setExecutable(false, false)) {
                System.out.println("Failed to set execute permission.");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}