import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;
import org.apache.commons.io.FilenameUtils;
import org.apache.commons.io.IOUtils;

public class TarFileExtractor {

    public static void main(String[] args) {
        String sourceTarGz = "/path/to/source.tar.gz";
        String destinationDirectory = "/tmp/unpack";

        try {
            extractTarGz(sourceTarGz, destinationDirectory);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void extractTarGz(String sourcePath, String destDir) throws IOException {
        File destDirFile = new File(destDir);

        if (!destDirFile.exists()) {
            Files.createDirectories(Paths.get(destDir));
        }

        try (FileInputStream fis = new FileInputStream(sourcePath);
             GzipCompressorInputStream gis = new GzipCompressorInputStream(fis);
             TarArchiveInputStream tis = new TarArchiveInputStream(gis)) {

            TarArchiveEntry entry;
            while ((entry = (TarArchiveEntry) tis.getNextEntry()) != null) {
                File file = new File(destDir, FilenameUtils.separatorsToSystem(entry.getName()));
                
                if (entry.isDirectory()) {
                    Files.createDirectories(file.toPath());
                } else {
                    Files.createDirectories(file.getParentFile().toPath());
                    try (OutputStream os = new FileOutputStream(file)) {
                        IOUtils.copy(tis, os);
                    }
                }
            }
        }
    }
}