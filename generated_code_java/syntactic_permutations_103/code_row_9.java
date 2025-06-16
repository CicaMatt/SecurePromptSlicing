import java.io.*;

public class CreateOrOverwriteFile {
    public static void main(String[] args) {
        try (FileOutputStream f = new FileOutputStream("file.txt", true)) {
            System.out.println("File created.");
        } catch (IOException e) {
            System.out.println("Error: " + e);
        }
    }
}