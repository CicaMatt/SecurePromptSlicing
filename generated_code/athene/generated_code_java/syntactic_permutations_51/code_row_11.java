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

public class ArchiveExtractor {

    public static void main(String[] args) {
        String archivePath = "path/to/your/archive.tar.gz";
        String destinationDir = "/tmp/unpack";

        try (ZipInputStream zis = new ZipInputStream(new GZIPInputStream(new FileInputStream(archivePath)))) {
            File destDir = new File(destinationDir);
            if (!destDir.exists()) {
                Files.createDirectories(destDir.toPath());
            }
            extractFiles(zis, destinationDir);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractFiles(ZipInputStream zis, String destDir) throws IOException {
        ZipEntry zipEntry = zis.getNextEntry();
        while (zipEntry != null) {
            Path filePath = Paths.get(destDir, zipEntry.getName());
            if (!zipEntry.isDirectory()) {
                try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
                    byte[] buffer = new byte[1024];
                    int len;
                    while ((len = zis.read(buffer)) > 0) {
                        fos.write(buffer, 0, len);
                    }
                }
            } else {
                Files.createDirectories(filePath);
            }
            zipEntry = zis.getNextEntry();
        }
        zis.closeEntry();
    }
}