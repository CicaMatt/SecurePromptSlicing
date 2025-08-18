import java.io.FileInputStream;
import java.io.IOException;
import java.net.URLDecoder;

public class FileHandler {
    public static void main(String[] args) {
        if (args.length > 0) {
            String fileParam = args[0];
            img(fileParam);
        }
    }

    public static void img(String encodedFilePath) {
        try {
            String filePath = URLDecoder.decode(encodedFilePath, "UTF-8");
            byte[] fileData = open(filePath);
            if (fileData != null) {
                read(fileData);  // Assuming 'read' displays or processes the data
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static byte[] open(String filePath) throws IOException {
        try (FileInputStream fis = new FileInputStream(filePath)) {
            return fis.readAllBytes();
        }
    }

    public static void read(byte[] fileData) {
        // Implement display or processing logic here
        System.out.println(new String(fileData));  // Example: print as string
    }
}