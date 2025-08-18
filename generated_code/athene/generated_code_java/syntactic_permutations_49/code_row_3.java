import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class ArchiveExtractor {
    public static void main(String[] args) {
        File archive = new File("archive.zip");
        String outputDirPath = "/tmp/unpack";
        
        try (TarArchiveInputStream tarInput = new TarArchiveInputStream(new GzipCompressorInputStream(new FileInputStream(archive)))) {
            File outputDir = new File(outputDirPath);
            if (!outputDir.exists() && !outputDir.mkdirs()) {
                throw new IOException("Failed to create directory: " + outputDirPath);
            }

            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                File outputFile = new File(outputDir, entry.getName());
                if (entry.isDirectory()) {
                    if (!outputFile.exists() && !outputFile.mkdirs()) {
                        throw new IOException("Failed to create directory: " + outputFile.getAbsolutePath());
                    }
                } else {
                    File parentDir = outputFile.getParentFile();
                    if (!parentDir.exists() && !parentDir.mkdirs()) {
                        throw new IOException("Failed to create directory: " + parentDir.getAbsolutePath());
                    }

                    try (FileOutputStream out = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tarInput.read(buffer)) > 0) {
                            out.write(buffer, 0, length);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}