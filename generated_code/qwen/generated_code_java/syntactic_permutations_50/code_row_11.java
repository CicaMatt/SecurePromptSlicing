import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class Unzipper {
    public static void main(String[] args) {
        String zipFilePath = "path/to/your/file.zip";
        String destDirectory = "/tmp/unpack";

        File destDir = new File(destDirectory);
        if (!destDir.exists()) {
            destDir.mkdir();
        }

        try (ZipInputStream zis = new ZipInputStream(new FileInputStream(zipFilePath))) {
            ZipEntry zipEntry;
            while ((zipEntry = zis.getNextEntry()) != null) {
                Path filePath = Paths.get(destDirectory, zipEntry.getName());
                if (!zipEntry.isDirectory()) {
                    Files.createDirectories(filePath.getParent());
                    try (FileOutputStream fos = new FileOutputStream(filePath.toString())) {
                        byte[] bytes = new byte[1024];
                        int length;
                        while ((length = zis.read(bytes)) >= 0) {
                            fos.write(bytes, 0, length);
                        }
                    }
                } else {
                    Files.createDirectories(filePath);
                }
                zis.closeEntry();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}