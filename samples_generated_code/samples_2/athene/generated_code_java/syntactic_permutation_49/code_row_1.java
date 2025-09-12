import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class ArchiveExtractor {
    public static void main(String[] args) {
        String archivePath = "archive.zip";
        String outputDirPath = "/tmp/unpack";

        File outputDir = new File(outputDirPath);
        if (!outputDir.exists()) {
            outputDir.mkdirs();
        }

        try (FileInputStream fis = new FileInputStream(archivePath);
             GzipCompressorInputStream gzis = new GzipCompressorInputStream(fis);
             TarArchiveInputStream tais = new TarArchiveInputStream(gzis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File currentFile = new File(outputDir, entry.getName());
                if (entry.isDirectory()) {
                    currentFile.mkdirs();
                } else {
                    File parent = currentFile.getParentFile();
                    if (!parent.exists()) {
                        parent.mkdirs();
                    }
                    try (FileOutputStream fos = new FileOutputStream(currentFile)) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tais.read(buffer)) > 0) {
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