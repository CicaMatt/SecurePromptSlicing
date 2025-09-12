import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class ArchiveExtractor {

    public static void main(String[] args) {
        try (TarArchiveInputStream tarIn = new TarArchiveInputStream(new GZIPInputStream(new FileInputStream("archive.tar.gz")))) {
            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                if (!tarIn.canReadEntryData(entry)) {
                    System.err.println("Cannot read data for " + entry.getName());
                    continue;
                }
                File destPath = new File("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(destPath.toPath());
                } else {
                    Files.copy(tarIn, destPath.toPath());
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        try (TarArchiveInputStream tarIn = new TarArchiveInputStream(new BZip2CompressorInputStream(new FileInputStream("archive.tar.bz2")))) {
            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                if (!tarIn.canReadEntryData(entry)) {
                    System.err.println("Cannot read data for " + entry.getName());
                    continue;
                }
                File destPath = new File("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(destPath.toPath());
                } else {
                    Files.copy(tarIn, destPath.toPath());
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}