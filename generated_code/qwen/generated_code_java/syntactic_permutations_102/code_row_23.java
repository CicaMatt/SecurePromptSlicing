import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        try {
            FileDescriptor fd = new FileDescriptor();
            FileOutputStream fos = new FileOutputStream("important_config", true);
            
            // Set file permissions (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
            // Note: Java does not provide direct way to set file permissions like C/C++ open() with mode flags
            // This is usually done using File.setReadable(), File.setWritable(), etc.
            File f = new File("important_config");
            f.setReadable(true, false);  // readable by all
            f.setWritable(true, true);   // writable by owner, readable by group

            String data = "important_config";
            fos.write(data.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}