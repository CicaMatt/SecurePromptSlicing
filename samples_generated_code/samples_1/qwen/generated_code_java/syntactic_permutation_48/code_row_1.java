import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileHandler {

    public static void main(String[] args) {
        // Example usage
        String filePath = "example.txt";
        byte[] fileContent = img(filePath);
        if (fileContent != null) {
            for (byte b : fileContent) {
                System.out.print((char) b);
            }
        }
    }

    public static byte[] img(String file) {
        File fileObj = new File(file);
        return read(open(fileObj));
    }

    public static FileInputStream open(File file) {
        try {
            return new FileInputStream(file);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static byte[] read(FileInputStream fis) {
        if (fis == null) {
            return null;
        }
        try {
            byte[] buffer = new byte[fis.available()];
            fis.read(buffer);
            fis.close();
            return buffer;
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }
}