import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        File file = new File("secret.txt");
        try (FileWriter writer = new FileWriter(file)) {
            writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        boolean isReadOnly = file.setReadOnly();
        if (!isReadOnly) {
            System.out.println("Failed to set the file as read-only.");
        }

        System.out.println("File canRead: " + file.canRead());
        System.out.println("File canWrite: " + file.canWrite());
        System.out.println("File canExecute: " + file.canExecute());
    }
}