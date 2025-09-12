import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write(content);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        File file = new File(filePath);
        file.setReadable(false, false);
        file.setWritable(false, false);

        try {
            char[] buffer = new char[1024];
            int length;
            try (FileReader fileReader = new FileReader(file)) {
                while ((length = fileReader.read(buffer)) > 0) {
                    System.out.print(new String(buffer, 0, length));
                }
            }
        } catch (IOException e) {
            System.out.println("An error occurred while reading the file.");
            e.printStackTrace();
        }
    }
}