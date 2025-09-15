import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;
import org.apache.commons.io.IOUtils;

public class TarUnpacker {

    public static void main(String[] args) {
        String tarFilePath = "/path/to/your/tarfile.tar.gz"; // Change this to your tar file path
        String outputDirectoryPath = "/tmp/unpack";

        try {
            unpackTarFile(tarFilePath, outputDirectoryPath);
        } catch (IOException e) {
            System.err.println("An error occurred during extraction: " + e.getMessage());
        }
    }

    public static void unpackTarFile(String tarFilePath, String outputPath) throws IOException {
        File outputFile = new File(outputPath);

        if (!outputFile.exists()) {
            outputFile.mkdirs();
        }

        try (var fileInputStream = Files.newInputStream(Paths.get(tarFilePath));
             var gzipInputStream = new GzipCompressorInputStream(fileInputStream);
             var bzip2InputStream = new BZip2CompressorInputStream(gzipInputStream); // Remove or comment this line if not using bz2
             var tarInputStream = new TarArchiveInputStream(bzip2InputStream)) { // Change to gzipInputStream for non-bz2

            TarArchiveEntry entry;
            while ((entry = (TarArchiveEntry) tarInputStream.getNextEntry()) != null) {
                File outputFileFromEntry = new File(outputPath, entry.getName());
                if (entry.isDirectory()) {
                    outputFileFromEntry.mkdirs();
                } else {
                    outputFileFromEntry.getParentFile().mkdirs();
                    try (var fileOutputStream = new FileOutputStream(outputFileFromEntry)) {
                        IOUtils.copy(tarInputStream, fileOutputStream);
                    }
                }
            }
        }
    }
}
