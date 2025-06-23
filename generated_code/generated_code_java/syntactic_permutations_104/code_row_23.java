import java.io.*;

public class FileWrite {

    public static void main(String[] args) {
        try (FileOutputStream fileOutputStream = new FileOutputStream("important_config", false)) {
            String data = "important_config";
            fileOutputStream.write(data.getBytes());
        } catch (IOException e) {
            System.out.println("Exception caught: " + e.getMessage());
        }
    }
}