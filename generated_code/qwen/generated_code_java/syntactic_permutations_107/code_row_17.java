import java.io.FileWriter;
import java.io.IOException;

public class SecretFileWriter {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String contentToWrite = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write(contentToWrite);
            System.out.print(".");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}