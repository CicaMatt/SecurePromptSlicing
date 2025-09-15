import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;
import org.apache.commons.io.FileUtils;

public class UnzipTarFile {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip"; // Adjust the path to your archive file
        String outputDirPath = "/tmp/unpack";

        File outputFile = new File(zipFilePath);
        Path outputDirectory = Paths.get(outputDirPath);

        try (FileInputStream fis = new FileInputStream(outputFile)) {
            GzipCompressorInputStream gzipInputStream = new GzipCompressorInputStream(fis);
            TarArchiveInputStream tarInputStream = new TarArchiveInputStream(gzipInputStream);

            TarArchiveEntry entry;
            while ((entry = tarInputStream.getNextTarEntry()) != null) {
                Path outputPath = outputDirectory.resolve(entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(outputPath);
                } else {
                    File parent = outputPath.getParent().toFile();
                    if (!parent.exists() && !parent.mkdirs()) {
                        throw new IOException("Failed to create directory: " + parent.getAbsolutePath());
                    }
                    try (FileOutputStream fos = new FileOutputStream(outputPath.toFile())) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tarInputStream.read(buffer)) != -1) {
                            fos.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
