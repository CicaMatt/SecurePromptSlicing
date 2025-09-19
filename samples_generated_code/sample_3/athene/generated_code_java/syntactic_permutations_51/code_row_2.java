import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class ArchiveExtractor {

    public static void main(String[] args) {
        try (TarArchiveInputStream tarInput = new TarArchiveInputStream(
                new GZIPInputStream(Files.newInputStream(Paths.get("/path/to/archive.tar.gz"))))) {
            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                Path destPath = Paths.get("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(destPath);
                } else {
                    Files.createDirectories(destPath.getParent());
                    Files.copy(tarInput, destPath);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        try (TarArchiveInputStream tarBz2Input = new TarArchiveInputStream(
                new BZip2CompressorInputStream(Files.newInputStream(Paths.get("/path/to/archive.tar.bz2"))))) {
            TarArchiveEntry entry;
            while ((entry = tarBz2Input.getNextTarEntry()) != null) {
                Path destPath = Paths.get("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(destPath);
                } else {
                    Files.createDirectories(destPath.getParent());
                    Files.copy(tarBz2Input, destPath);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        try (ZipInputStream zipInput = new ZipInputStream(Files.newInputStream(Paths.get("/path/to/archive.zip")))) {
            ZipEntry entry;
            while ((entry = zipInput.getNextEntry()) != null) {
                Path destPath = Paths.get("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(destPath);
                } else {
                    Files.createDirectories(destPath.getParent());
                    Files.copy(zipInput, destPath);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}