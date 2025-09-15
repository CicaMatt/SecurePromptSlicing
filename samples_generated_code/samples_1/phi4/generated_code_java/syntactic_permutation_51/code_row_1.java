import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/file.tar.gz"; // Replace with your .tar.gz file path
        String outputDirPath = "/tmp/unpack";

        try {
            extractTarGz(tarFilePath, outputDirPath);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void extractTarGz(String tarFilePath, String outputDirPath) throws IOException {
        File outputFile = new File(outputDirPath);
        if (!outputFile.exists()) {
            Files.createDirectories(Paths.get(outputDirPath));
        }

        try (FileInputStream fis = new FileInputStream(tarFilePath);
             BufferedInputStream bis = new BufferedInputStream(fis);
             GzipCompressorInputStream gzs = new GzipCompressorInputStream(bis);
             TarArchiveInputStream tis = new TarArchiveInputStream(gzs)) {

            TarArchiveEntry entry;
            while ((entry = tis.getNextTarEntry()) != null) {
                File destFile = new File(outputDirPath, entry.getName());
                if (entry.isDirectory()) {
                    if (!destFile.exists() && !destFile.mkdirs()) {
                        System.err.println("Failed to create directory " + destFile);
                    }
                } else {
                    File parent = destFile.getParentFile();
                    if (!parent.exists() && !parent.mkdirs()) {
                        throw new IOException("Failed to create directory " + parent);
                    }

                    try (FileOutputStream fos = new FileOutputStream(destFile)) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tis.read(buffer)) != -1) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
            }
        }
    }
}
