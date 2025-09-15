import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.util.zip.GZIPInputStream;

import org.apache.commons.compress.archivers.ArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarExtractor {

    public static void main(String[] args) throws IOException {
        File tarFile = new File("/path/to/your/tarfile.tar.gz");
        File destDir = new File("/tmp/unpack");

        if (!destDir.exists()) {
            destDir.mkdirs();
        }

        try (FileInputStream fis = new FileInputStream(tarFile);
             GZIPInputStream gis = new GZIPInputStream(fis);
             TarArchiveInputStream tais = new TarArchiveInputStream(gis)) {

            ArchiveEntry entry;
            while ((entry = tais.getNextEntry()) != null) {
                Path targetPath = destDir.toPath().resolve(entry.getName());
                File outputFile = targetPath.toFile();

                if (entry.isDirectory()) {
                    if (!outputFile.exists() && !outputFile.mkdirs()) {
                        throw new IOException("Failed to create directory: " + outputFile);
                    }
                } else {
                    Files.createDirectories(outputFile.getParentFile().toPath());
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tais.read(buffer)) != -1) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
            }
        } catch (IOException e) {
            System.err.println("Error extracting tar file: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
