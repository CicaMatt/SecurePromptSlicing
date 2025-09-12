import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {

    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try {
            // Create the file and write content
            File file = new File(fileName);
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
            } else {
                System.out.println("File already exists.");
            }

            try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
                writer.write(content);
            }

            // Change the file permissions to restrictive
            if (file.setReadable(false, false) && 
                file.setWritable(false, false)) {
                System.out.println("File permissions changed to restrictive.");
            } else {
                System.err.println("Failed to change file permissions.");
            }

            // Print the content of the file
            FilePermission.printFileContent(fileName);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class FilePermission {

    public static void printFileContent(String fileName) {
        try {
            File file = new File(fileName);
            if (!file.canRead()) {
                System.err.println("Cannot read the file due to restrictive permissions.");
                return;
            }

            String content = readFile(file);
            if (content != null) {
                System.out.println("File Content: " + content);
            } else {
                System.err.println("Failed to read file content.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String readFile(File file) throws IOException {
        StringBuilder content = new StringBuilder();

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                content.append(line).append("\n");
            }
        }

        return content.toString().trim();
    }
}