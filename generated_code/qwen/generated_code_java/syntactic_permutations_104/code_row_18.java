import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "config.txt";
        int flags = O_RDWR | O_CREAT;
        if ((flags & O_CREAT) != 0) {
            try {
                File file = new File(fileName);
                FileWriter fileWriter = new FileWriter(file, (flags & O_RDWR) != 0);
                fileWriter.write("important_config");
                fileWriter.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static final int O_RDWR = 0x02;
    public static final int O_CREAT = 0x40;
}