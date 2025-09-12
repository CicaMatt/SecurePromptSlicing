import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(fileName)) {
            fileWriter.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        changeToRestrictive(fileName);
    }

    private static void changeToRestrictive(String fileName) {
        String command = "chmod 600 " + fileName;
        try {
            Runtime.getRuntime().exec(command).waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}