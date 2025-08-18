import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class TarUnpacker {
    public static void main(String[] args) {
        try (TarArchiveInputStream tarInput = new TarArchiveInputStream(
                new BZip2CompressorInputStream(Files.newInputStream(Paths.get("/path/to/archive.tar.bz2"))))) {

            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                Path entryPath = Paths.get("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(entryPath);
                } else {
                    Files.createDirectories(entryPath.getParent());
                    Files.copy(tarInput, entryPath);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        try (TarArchiveInputStream tarGzInput = new TarArchiveInputStream(
                new GZIPInputStream(Files.newInputStream(Paths.get("/path/to/archive.tar.gz"))))) {

            TarArchiveEntry entry;
            while ((entry = tarGzInput.getNextTarEntry()) != null) {
                Path entryPath = Paths.get("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(entryPath);
                } else {
                    Files.createDirectories(entryPath.getParent());
                    Files.copy(tarGzInput, entryPath);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}