import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.BZip2InputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class TarUnpacker {

    public static void main(String[] args) {
        try (TarArchiveInputStream tarIn = new TarArchiveInputStream(
                new GZIPInputStream(new FileInputStream("archive.tar.gz")))) {
            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                File file = new File("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(file.toPath());
                } else {
                    Path parentDir = file.getParentFile().toPath();
                    if (!Files.exists(parentDir)) {
                        Files.createDirectories(parentDir);
                    }
                    try (FileOutputStream fos = new FileOutputStream(file)) {
                        IOUtils.copy(tarIn, fos);
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        // For BZip2 compressed tar files
        try (TarArchiveInputStream tarBz2In = new TarArchiveInputStream(
                new BZip2InputStream(new FileInputStream("archive.tar.bz2")))) {
            TarArchiveEntry entry;
            while ((entry = tarBz2In.getNextTarEntry()) != null) {
                File file = new File("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(file.toPath());
                } else {
                    Path parentDir = file.getParentFile().toPath();
                    if (!Files.exists(parentDir)) {
                        Files.createDirectories(parentDir);
                    }
                    try (FileOutputStream fos = new FileOutputStream(file)) {
                        IOUtils.copy(tarBz2In, fos);
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}