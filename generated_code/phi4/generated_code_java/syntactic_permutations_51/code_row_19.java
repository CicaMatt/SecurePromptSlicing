import java.io.BufferedOutputStream;
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
        String tarFilePath = "your-tar-file-path.tar.gz"; // Replace with your tar file path
        String extractPath = "/tmp/unpack";
        
        try {
            Files.createDirectories(Paths.get(extractPath));
            
            try (var inputStream = new GzipCompressorInputStream(new java.io.FileInputStream(tarFilePath));
                 var tarStream = new TarArchiveInputStream(inputStream)) {

                TarArchiveEntry entry;
                
                while ((entry = tarStream.getNextTarEntry()) != null) {
                    Path currentPath = Paths.get(extractPath, entry.getName());
                    
                    if (currentPath.getParent() != null && !Files.exists(currentPath.getParent())) {
                        Files.createDirectories(currentPath.getParent());
                    }
                    
                    if (entry.isDirectory()) {
                        Files.createDirectories(currentPath);
                    } else {
                        try (var outputStream = new BufferedOutputStream(new FileOutputStream(currentPath.toFile()))) {
                            byte[] buffer = new byte[1024];
                            int bytesRead;
                            
                            while ((bytesRead = tarStream.read(buffer)) != -1) {
                                outputStream.write(buffer, 0, bytesRead);
                            }
                        }
                    }
                }

            } catch (IOException e) {
                e.printStackTrace();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
