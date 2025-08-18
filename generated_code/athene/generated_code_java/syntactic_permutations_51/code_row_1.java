import java.io.InputStream;
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
    public static void main(String[] args) throws Exception {
        try (InputStream fileInputStream = Files.newInputStream(Paths.get("/path/to/archive.tar.gz"));
             InputStream gzipInputStream = new GZIPInputStream(fileInputStream);
             TarArchiveInputStream tarInputStream = new TarArchiveInputStream(gzipInputStream)) {

            TarArchiveEntry entry;
            while ((entry = tarInputStream.getNextTarEntry()) != null) {
                Path entryPath = Paths.get("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(entryPath);
                } else {
                    Files.createDirectories(entryPath.getParent());
                    try (InputStream entryInputStream = tarInputStream) {
                        Files.copy(entryInputStream, entryPath);
                    }
                }
            }
        }

        try (InputStream fileInputStream = Files.newInputStream(Paths.get("/path/to/archive.tar.bz2"));
             InputStream bzip2InputStream = new BZip2CompressorInputStream(fileInputStream);
             TarArchiveInputStream tarInputStream = new TarArchiveInputStream(bzip2InputStream)) {

            TarArchiveEntry entry;
            while ((entry = tarInputStream.getNextTarEntry()) != null) {
                Path entryPath = Paths.get("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(entryPath);
                } else {
                    Files.createDirectories(entryPath.getParent());
                    try (InputStream entryInputStream = tarInputStream) {
                        Files.copy(entryInputStream, entryPath);
                    }
                }
            }
        }

        try (InputStream fileInputStream = Files.newInputStream(Paths.get("/path/to/regular/file.txt"))) {
            // Use the InputStream for reading or processing the file
            IOUtils.copy(fileInputStream, Files.newOutputStream(Paths.get("/tmp/unpack/copyOfFile.txt")));
        }
    }
}