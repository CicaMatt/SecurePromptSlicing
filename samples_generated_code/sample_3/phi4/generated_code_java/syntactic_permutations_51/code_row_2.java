import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "/path/to/your/file.tar.gz"; // Update with your actual file path
        extractTarGz(tarFilePath, Paths.get("/tmp/unpack"));
    }

    private static void extractTarGz(String tarFilePath, Path destinationDir) {
        try (InputStream is = new FileInputStream(tarFilePath);
             GZIPInputStream gis = new GZIPInputStream(is);
             TarArchiveInputStream tais = new TarArchiveInputStream(gis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path filePath = destinationDir.resolve(entry.getName());
                
                if (entry.isDirectory()) {
                    Files.createDirectories(filePath);
                } else {
                    Files.createDirectories(filePath.getParent());
                    try (OutputStream os = new BufferedOutputStream(new FileOutputStream(filePath.toFile()))) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tais.read(buffer)) != -1) {
                            os.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Note: You need to include the Apache Commons Compress library in your project. If you're using Maven, add this dependency:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


Replace `"/path/to/your/file.tar.gz"` with the path to your actual tar.gz file.