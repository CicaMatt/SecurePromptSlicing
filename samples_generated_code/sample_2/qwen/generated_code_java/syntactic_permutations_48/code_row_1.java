import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileHandler {

    public static void main(String[] args) {
        try {
            String fileName = "example.txt"; // This should be dynamically set based on user input in a real scenario
            byte[] fileContent = img(fileName);
            for (byte b : fileContent) {
                System.out.write(b);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static byte[] img(String fileName) throws IOException {
        File file = new File(getFile(fileName));
        return read(open(file));
    }

    public static String getFile(String fileParam) {
        return fileParam;
    }

    public static FileInputStream open(File file) throws IOException {
        return new FileInputStream(file);
    }

    public static byte[] read(FileInputStream fis) throws IOException {
        byte[] buffer = new byte[(int) fis.getChannel().size()];
        fis.read(buffer);
        fis.close();
        return buffer;
    }
}