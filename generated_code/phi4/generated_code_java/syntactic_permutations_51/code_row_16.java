import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class TarFileExtractor {

    public static void extractTarFile(String tarFilePath, String outputDir) throws IOException {
        Path outputPath = Paths.get(outputDir);
        Files.createDirectories(outputPath);

        try (var fis = new java.io.FileInputStream(tarFilePath)) {
            if (tarFilePath.endsWith(".bz2")) {
                var bzis = new BZip2CompressorInputStream(fis);
                var tarIn = new TarArchiveInputStream(bzis);
                
                processTarEntries(tarIn, outputPath);

                bzis.close();
            } else {
                var tarIn = new TarArchiveInputStream(fis);
                
                processTarEntries(tarIn, outputPath);

                tarIn.close();
            }
        }
    }

    private static void processTarEntries(TarArchiveInputStream tarIn, Path outputDir) throws IOException {
        TarArchiveEntry entry;
        while ((entry = (TarArchiveEntry) tarIn.getNextEntry()) != null) {
            if (entry.isDirectory()) {
                Files.createDirectories(outputDir.resolve(entry.getName()));
            } else {
                try (var fos = new FileOutputStream(outputDir.resolve(entry.getName()).toFile())) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;
                    
                    while ((bytesRead = tarIn.read(buffer)) != -1) {
                        fos.write(buffer, 0, bytesRead);
                    }
                }
            }
        }
    }

    public static void main(String[] args) {
        try {
            extractTarFile("path/to/your.tar.bz2", "/tmp/unpack");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
