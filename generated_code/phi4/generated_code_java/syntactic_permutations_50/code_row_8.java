import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class ZipToTarExtractor {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String outputDirectoryPath = "/tmp/unpack";

        File outputFile = new File(zipFilePath);

        if (outputFile.exists()) {
            try {
                // Create the output directory if it does not exist.
                Files.createDirectories(Paths.get(outputDirectoryPath));

                // Open the ZIP file as an input stream.
                try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(outputFile))) {
                    TarArchiveInputStream tarInput = new TarArchiveInputStream(bis);
                    
                    TarArchiveEntry entry;
                    while ((entry = tarInput.getNextTarEntry()) != null) {
                        File outputFile = new File(outputDirectoryPath, entry.getName());
                        
                        if (entry.isDirectory()) {
                            if (!outputFile.exists() && !outputFile.mkdirs())
                                throw new IOException("Failed to create directory " + outputFile.getAbsolutePath());
                        } else {
                            // Ensure the parent directories exist.
                            Files.createDirectories(outputFile.toPath().getParent());

                            try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                                byte[] buffer = new byte[1024];
                                int bytesRead;
                                while ((bytesRead = tarInput.read(buffer)) != -1) {
                                    fos.write(buffer, 0, bytesRead);
                                }
                            }
                        }
                    }
                } catch (IOException e) {
                    System.err.println("Error processing the archive: " + e.getMessage());
                }
            } catch (IOException e) {
                System.err.println("Failed to open the zip file: " + e.getMessage());
            }
        } else {
            System.err.println("The specified zip file does not exist.");
        }
    }
}
