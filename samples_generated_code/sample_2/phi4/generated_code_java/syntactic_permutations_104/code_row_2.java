import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "example.txt";
        
        try (FileOutputStream fos = openFile(fileName, true)) {
            String data = "Hello, World!";
            writeData(fos, data);
            System.out.println("Data written to file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static FileOutputStream openFile(String fileName, boolean createIfNotExists) throws IOException {
        File file = new File(fileName);
        if (createIfNotExists && !file.exists()) {
            file.createNewFile();
        }
        return new FileOutputStream(file, true); // Open for reading and writing
    }

    private static void writeData(FileOutputStream fos, String data) throws IOException {
        byte[] bytes = data.getBytes();
        fos.write(bytes);
    }
}