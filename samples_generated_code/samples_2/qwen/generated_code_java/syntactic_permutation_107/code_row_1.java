import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FilePermissionExample {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String contentToWrite = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write(contentToWrite);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        File file = new File(filePath);

        if (!file.setExecutable(false) || !file.setReadable(false, true) || !file.setWritable(false)) {
            System.out.println("Failed to set restrictive permissions for the file.");
        } else {
            System.out.println("Restrictive permissions have been successfully set for the file.");
        }

        try {
            Process process = Runtime.getRuntime().exec("ls -l " + filePath);
            java.util.Scanner scanner = new java.util.Scanner(process.getInputStream()).useDelimiter("\\A");
            String output = scanner.hasNext() ? scanner.next() : "";
            System.out.println(output);
        } catch (IOException e) {
            System.out.println("An error occurred while checking file permissions.");
            e.printStackTrace();
        }
    }
}