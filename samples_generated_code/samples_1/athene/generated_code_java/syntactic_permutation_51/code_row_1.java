import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class UnzipExample {
    public static void main(String[] args) {
        String tarFilePath = "example.tar.gz";
        String outputDirectoryPath = "/tmp/unpack";

        try (ZipInputStream zis = new ZipInputStream(new GZIPInputStream(new FileInputStream(tarFilePath)))) {
            File outputDir = new File(outputDirectoryPath);
            if (!outputDir.exists()) {
                Files.createDirectories(Paths.get(outputDirectoryPath));
            }

            ZipEntry zipEntry;
            while ((zipEntry = zis.getNextEntry()) != null) {
                Path filePath = Paths.get(outputDirectoryPath, zipEntry.getName());
                if (zipEntry.isDirectory()) {
                    Files.createDirectories(filePath);
                } else {
                    try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = zis.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}