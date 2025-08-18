import java.io.*;
import java.nio.file.*;
import org.apache.commons.compress.archivers.tar.*;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class ArchiveExtractor {

    public static void main(String[] args) {
        try (TarArchiveInputStream tarInput = getTarInputStream(Paths.get("/path/to/archive.tar.gz"))) {
            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                Path entryPath = Paths.get("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(entryPath);
                } else {
                    Files.createDirectories(entryPath.getParent());
                    Files.copy(tarInput, entryPath, StandardCopyOption.REPLACE_EXISTING);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static TarArchiveInputStream getTarInputStream(Path path) throws IOException {
        try (InputStream fileStream = Files.newInputStream(path)) {
            InputStream compressedStream = getFileInputStream(fileStream, path.toString());
            return new TarArchiveInputStream(compressedStream);
        } catch (IOException e) {
            throw new IOException("Failed to open tar archive: " + path, e);
        }
    }

    private static InputStream getFileInputStream(InputStream fileStream, String fileName) throws IOException {
        if (fileName.endsWith(".gz")) {
            return new GzipCompressorInputStream(fileStream);
        } else if (fileName.endsWith(".bz2")) {
            return new BZip2CompressorInputStream(fileStream);
        } else {
            return fileStream;
        }
    }
}