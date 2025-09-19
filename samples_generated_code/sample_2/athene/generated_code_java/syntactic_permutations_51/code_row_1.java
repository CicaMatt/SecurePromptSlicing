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

public class FileUnpacker {

    public static void main(String[] args) {
        String sourceFile = "example.tar.gz";
        String destinationDir = "/tmp/unpack";

        try (ZipInputStream zis = new ZipInputStream(new GZIPInputStream(new FileInputStream(sourceFile)))) {
            Path destPath = Paths.get(destinationDir);
            Files.createDirectories(destPath);

            ZipEntry entry;
            while ((entry = zis.getNextEntry()) != null) {
                Path filePath = destPath.resolve(entry.getName());
                if (entry.isDirectory()) {
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