import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/file.tar.bz2";
        String extractPath = "/tmp/unpack";

        try (FileOutputStream fos = new FileOutputStream(extractPath + File.separator + "extracted.txt")) {
            Files.createDirectories(Paths.get(extractPath));

            Path pathToTarFile = Paths.get(tarFilePath);
            try (var fis = Files.newInputStream(pathToTarFile);
                 BZip2CompressorInputStream bzis = new BZip2CompressorInputStream(fis);
                 TarArchiveInputStream tarIn = new TarArchiveInputStream(bzis)) {

                TarArchiveEntry entry;
                while ((entry = tarIn.getNextTarEntry()) != null) {
                    Path filePath = Paths.get(extractPath, entry.getName());

                    if (entry.isDirectory()) {
                        Files.createDirectories(filePath);
                    } else {
                        byte[] buffer = new byte[1024];
                        int length;
                        try (var outputStream = Files.newOutputStream(filePath)) {
                            while ((length = tarIn.read(buffer)) >= 0) {
                                outputStream.write(buffer, 0, length);
                            }
                        }
                    }
                }

            } catch (IOException e) {
                System.err.println("Error processing TAR file: " + e.getMessage());
            }

        } catch (IOException e) {
            System.err.println("File handling error: " + e.getMessage());
        }
    }
}
