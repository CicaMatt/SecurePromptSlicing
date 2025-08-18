import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class ConfigHandler {
    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config";

        try {
            writeToFile(filePath, content);
            System.out.println("File written successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void writeToFile(String fileName, String data) throws IOException {
        Path path = Paths.get(fileName);
        byte[] bytes = data.getBytes();

        Files.write(path, bytes, StandardOpenOption.CREATE, StandardOpenOption.WRITE,
                java.nio.file.attribute.PosixFilePermissions.asFileAttribute(
                        java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--")));
    }
}