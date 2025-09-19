import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarfileUnzip {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/file.tar.gz";
        String outputDirectoryPath = "/tmp/unpack";

        try {
            unzipTarGz(tarFilePath, outputDirectoryPath);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void unzipTarGz(String tarFilePath, String outputDirPath) throws IOException {
        Path outputPath = Paths.get(outputDirPath);

        if (!Files.exists(outputPath)) {
            Files.createDirectories(outputPath);
        }

        try (
            GZIPInputStream gzipStream = new GZIPInputStream(new java.io.FileInputStream(tarFilePath));
            TarArchiveInputStream tarInput = new TarArchiveInputStream(gzipStream)
        ) {
            TarArchiveEntry entry;
            while ((entry = (TarArchiveEntry) tarInput.getNextEntry()) != null) {
                File outputFile = outputPath.resolve(entry.getName()).toFile();
                if (entry.isDirectory()) {
                    if (!outputFile.exists() && !outputFile.mkdirs()) {
                        throw new IOException("Failed to create directory: " + outputFile);
                    }
                } else {
                    Files.createDirectories(outputFile.getParentFile().toPath());
                    try (FileOutputStream outputStream = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tarInput.read(buffer)) != -1) {
                            outputStream.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }
        }
    }
}