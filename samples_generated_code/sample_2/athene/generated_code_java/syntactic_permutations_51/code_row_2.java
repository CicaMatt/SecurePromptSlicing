import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class ArchiveUnpacker {
    public static void main(String[] args) {
        try (ZipInputStream zis = new ZipInputStream(new GZIPInputStream(new FileInputStream("/path/to/archive.tar.gz")))) {
            ZipEntry entry;
            while ((entry = zis.getNextEntry()) != null) {
                Path path = Paths.get("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(path);
                } else {
                    File parent = path.getParent().toFile();
                    if (!parent.exists() && !parent.mkdirs()) {
                        throw new IOException("Failed to create directory: " + parent);
                    }
                    try (FileOutputStream fos = new FileOutputStream(path.toFile())) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = zis.read(buffer)) > 0) {
                            fos.write(buffer, 0, length);
                        }
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}