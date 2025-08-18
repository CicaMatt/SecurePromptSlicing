import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.CompressorStreamFactory;
import org.apache.commons.compress.utils.IOUtils;

public class TarExtractor {

    public static void main(String[] args) {
        String inputTarGzFilePath = "/path/to/your/inputfile.tar.gz";
        String outputDirectoryPath = "/tmp/unpack";

        extractTarGz(inputTarGzFilePath, outputDirectoryPath);
    }

    private static void extractTarGz(String tarGzFilePath, String outputDir) {
        try (FileInputStream fileInputStream = new FileInputStream(tarGzFilePath)) {
            CompressorStreamFactory compressorStreamFactory = new CompressorStreamFactory();
            org.apache.commons.compress.compressors.CompressorInputStream gzipCompressedStream =
                    compressorStreamFactory.createCompressorInputStream("gz", fileInputStream);

            TarArchiveInputStream tarInput = new TarArchiveInputStream(gzipCompressedStream);
            TarArchiveEntry entry;

            while ((entry = (TarArchiveEntry) tarInput.getNextEntry()) != null) {
                String filePath = outputDir + File.separator + entry.getName();
                File outputFile = new File(filePath);

                if (entry.isDirectory()) {
                    if (!outputFile.exists() && !outputFile.mkdirs()) {
                        throw new IOException("Failed to create directory: " + filePath);
                    }
                } else {
                    File parentDirectory = outputFile.getParentFile();
                    if (!parentDirectory.exists() && !parentDirectory.mkdirs()) {
                        throw new IOException("Failed to create directory: " + parentDirectory.getAbsolutePath());
                    }

                    try (FileOutputStream outputStream = new FileOutputStream(outputFile)) {
                        IOUtils.copy(tarInput, outputStream);
                    }
                }
            }
        } catch (IOException e) {
            System.err.println("An error occurred during the extraction process.");
            e.printStackTrace();
        }
    }
}