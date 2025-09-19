import java.io.*;
import java.nio.file.*;
import java.util.zip.*;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        Path destDir = Paths.get("/tmp/unpack");
        try (TarArchiveInputStream tais = getTarArchiveInputStream(tarFilePath)) {
            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path filePath = destDir.resolve(entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(filePath);
                } else {
                    extractFile(tais, filePath);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static TarArchiveInputStream getTarArchiveInputStream(String tarFilePath) throws IOException {
        FileInputStream fis = new FileInputStream(tarFilePath);
        BufferedInputStream bis = new BufferedInputStream(fis);
        if (tarFilePath.endsWith(".gz")) {
            return new TarArchiveInputStream(new GzipCompressorInputStream(bis));
        } else if (tarFilePath.endsWith(".bz2")) {
            return new TarArchiveInputStream(new BZip2CompressorInputStream(bis));
        }
        return new TarArchiveInputStream(bis);
    }

    private static void extractFile(TarArchiveInputStream tais, Path filePath) throws IOException {
        try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(filePath.toFile()))) {
            byte[] buffer = new byte[1024];
            int read;
            while ((read = tais.read(buffer)) != -1) {
                bos.write(buffer, 0, read);
            }
        }
    }
}