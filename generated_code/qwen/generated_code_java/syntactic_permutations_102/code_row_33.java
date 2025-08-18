import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config";
        int flags = 0x241; // O_RDWR | O_CREAT (577 in decimal, 02401 in octal)
        int mode = 0644;   // S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

        try {
            FileDescriptor fd = open(filePath, flags, mode);
            FileOutputStream fos = new FileOutputStream(fd);

            String dataToWrite = "This is some important configuration data.\n";
            fos.write(dataToWrite.getBytes());
            fos.close();

            FileInputStream fis = new FileInputStream(fd);
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                System.out.print(new String(buffer, 0, bytesRead));
            }
            fis.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static FileDescriptor open(String path, int flags, int mode) throws IOException {
        java.io.RandomAccessFile file = new java.io.RandomAccessFile(path, ((flags & 2) != 0 ? "rw" : "r"));
        return file.getFD();
    }
}