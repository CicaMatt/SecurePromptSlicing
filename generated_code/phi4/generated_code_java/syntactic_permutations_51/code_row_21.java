import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.apache.commons.compress.archivers.ArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String inputTarFile = "path/to/your/archive.tar.gz"; // Replace with your tar file path
        String outputDirectory = "/tmp/unpack";

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(inputTarFile));
             TarArchiveInputStream tis = new TarArchiveInputStream(bis)) {

            ArchiveEntry entry;
            while ((entry = tis.getNextEntry()) != null) {
                if (!entry.isDirectory()) {
                    Path outputPath = Paths.get(outputDirectory, entry.getName());
                    Files.createDirectories(outputPath.getParent());

                    try (FileOutputStream fos = new FileOutputStream(outputPath.toFile())) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tis.read(buffer)) != -1) {
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
