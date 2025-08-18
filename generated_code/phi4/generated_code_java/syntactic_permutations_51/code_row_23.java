import java.io.IOException;
import java.nio.file.*;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarFileExtractor {

    public static void main(String[] args) throws IOException {
        Path source = Paths.get("your-archive.tar.gz"); // Replace with your tar file path
        Path targetDir = Paths.get("/tmp/unpack");

        try (TarArchiveInputStream tarInput = new TarArchiveInputStream(new GZIPInputStream(Files.newInputStream(source)))) {
            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                Path currentTarget = targetDir.resolve(entry.getName());
                
                if (entry.isDirectory()) {
                    Files.createDirectories(currentTarget);
                } else {
                    Files.createDirectories(currentTarget.getParent());
                    try (var outputStream = Files.newOutputStream(currentTarget)) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tarInput.read(buffer)) != -1) {
                            outputStream.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }
        } catch (IOException e) {
            System.err.println("Error processing the file: " + e.getMessage());
            throw e;
        }

        System.out.println("Extraction complete.");
    }
}


**Dependencies Needed**:  
To run this code, you need to include the Apache Commons Compress library in your project. You can add it using Maven with the following dependency:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version> <!-- Make sure to check for the latest version -->
</dependency>


Or, if you're using Gradle, add this:


implementation 'org.apache.commons:commons-compress:1.21'


This code reads a `.tar.gz` file and extracts its contents into `/tmp/unpack`. Make sure to replace `"your-archive.tar.gz"` with the actual path of your tar archive.