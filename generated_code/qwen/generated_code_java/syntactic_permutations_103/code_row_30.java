import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            open(filePath, true, true, false);
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void open(String path, boolean oCreat, boolean oTrunc, boolean oExcl) throws IOException {
        File file = new File(path);

        if (!oCreat && !file.exists()) {
            throw new IOException("File does not exist and O_CREAT is false.");
        }

        if (oExcl && file.exists()) {
            throw new IOException("File already exists and O_EXCL is true.");
        }

        if (oTrunc) {
            FileOutputStream fos = new FileOutputStream(file, false);
            fos.close();
        } else {
            new FileOutputStream(file, !oTrunc).close();
        }
    }
}