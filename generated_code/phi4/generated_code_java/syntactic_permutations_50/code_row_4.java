import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destinationPath = "/tmp/unpack";

        File destDir = new File(destinationPath);
        if (!destDir.exists()) {
            destDir.mkdirs();
        }

        extractTarGz(tarFilePath, destinationPath);
    }

    private static void extractTarGz(String tarGzFilePath, String outputDir) {
        Path outputPath = Paths.get(outputDir);

        try (FileInputStream fis = new FileInputStream(new File(tarGzFilePath));
             GzipCompressorInputStream gzIn = new GzipCompressorInputStream(fis);
             TarArchiveInputStream tarIn = new TarArchiveInputStream(gzIn)) {

            TarArchiveEntry entry;
            while ((entry = (TarArchiveEntry) tarIn.getNextEntry()) != null) {
                Path outputPathEntry = outputPath.resolve(entry.getName());

                if (entry.isDirectory()) {
                    Files.createDirectories(outputPathEntry);
                } else {
                    Files.createDirectories(outputPathEntry.getParent());
                    try (FileOutputStream fos = new FileOutputStream(outputPathEntry.toFile())) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tarIn.read(buffer)) >= 0) {
                            fos.write(buffer, 0, length);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}