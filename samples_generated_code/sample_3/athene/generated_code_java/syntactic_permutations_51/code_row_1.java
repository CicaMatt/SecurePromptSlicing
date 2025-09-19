import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class UnzipTarfile {

    public static void main(String[] args) {
        String tmpDir = "/tmp/unpack";
        try (ZipInputStream zis = new ZipInputStream(new FileInputStream("archive.zip"))) {
            ZipEntry entry;
            while ((entry = zis.getNextEntry()) != null) {
                Path filePath = Paths.get(tmpDir, entry.getName());
                if (!entry.isDirectory()) {
                    Files.createDirectories(filePath.getParent());
                    try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = zis.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
                zis.closeEntry();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // For tar.gz files
        try (GZIPInputStream gzis = new GZIPInputStream(new FileInputStream("archive.tar.gz"));
             java.util.zip.ZipInputStream tis = new ZipInputStream(gzis)) {
            ZipEntry entry;
            while ((entry = tis.getNextEntry()) != null) {
                Path filePath = Paths.get(tmpDir, entry.getName());
                if (!entry.isDirectory()) {
                    Files.createDirectories(filePath.getParent());
                    try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tis.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
                tis.closeEntry();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}