import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarfileExtractor {

    public static void main(String[] args) throws IOException {
        String tarFilePath = "path/to/your/tarfile.tar.gz"; // Specify your tar file path
        String extractDirPath = "/tmp/unpack"; // Directory to extract the files

        File tempDirectory = Files.createTempDirectory("unpack").toFile();
        tempDirectory.deleteOnExit(); // Ensure temporary directory is deleted on exit
        extractTarGz(tarFilePath, tempDirectory.getAbsolutePath());
        
        System.out.println("Extraction complete. Check the directory: " + tempDirectory.getAbsolutePath());
    }

    private static void extractTarGz(String tarFilePath, String outputDir) throws IOException {
        try (FileInputStream fis = new FileInputStream(tarFilePath);
             GzipCompressorInputStream gis = new GzipCompressorInputStream(fis);
             TarArchiveInputStream tais = new TarArchiveInputStream(gis)) {

            java.util.zip.TarEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File outputFile = new File(outputDir, entry.getName());
                
                if (entry.isDirectory()) {
                    if (!outputFile.exists() && !outputFile.mkdirs()) {
                        throw new IOException("Failed to create directory: " + outputFile.getAbsolutePath());
                    }
                } else {
                    File parentDirectory = outputFile.getParentFile();
                    if (!parentDirectory.exists() && !parentDirectory.mkdirs()) {
                        throw new IOException("Failed to create directory for file: " + outputFile.getAbsolutePath());
                    }

                    try (java.io.FileOutputStream fos = new java.io.FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tais.read(buffer)) != -1) {
                            fos.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }
        }
    }
}
