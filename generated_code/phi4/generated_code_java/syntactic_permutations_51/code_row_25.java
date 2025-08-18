import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import org.apache.commons.compress.archivers.ArchiveEntry;
import org.apache.commons.compress.archivers.ArchiveException;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        String inputTarFilePath = "/path/to/your/file.tar.gz";
        String outputDirectoryPath = "/tmp/unpack";

        try {
            extractTarGz(inputTarFilePath, outputDirectoryPath);
        } catch (IOException | ArchiveException e) {
            e.printStackTrace();
        }
    }

    public static void extractTarGz(String tarFilePath, String outputDir) throws IOException, ArchiveException {
        Path outputPath = Paths.get(outputDir);

        if (!Files.exists(outputPath)) {
            Files.createDirectories(outputPath);
        }

        try (FileInputStream fileInputStream = new FileInputStream(tarFilePath);
             TarArchiveInputStream tarInput = new TarArchiveInputStream(fileInputStream)) {

            ArchiveEntry entry;

            while ((entry = tarInput.getNextTarEntry()) != null) {
                Path destFilePath = outputPath.resolve(entry.getName());

                if (entry.isDirectory()) {
                    Files.createDirectories(destFilePath);
                } else {
                    File parentDirectory = destFilePath.getParent().toFile();
                    if (!parentDirectory.exists() && !parentDirectory.mkdirs()) {
                        throw new IOException("Failed to create directories for " + destFilePath);
                    }

                    try (FileOutputStream fileOutput = new FileOutputStream(destFilePath.toFile())) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;

                        while ((bytesRead = tarInput.read(buffer)) != -1) {
                            fileOutput.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }
        }
    }
}


**Note:** This code uses Apache Commons Compress library to handle TAR and GZIP formats. You need to include the following dependency in your `pom.xml` if you're using Maven:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


Make sure to replace `"/path/to/your/file.tar.gz"` with the actual path of your TAR.GZ file before running the program.