import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class ArchiveExtractor {
    public static void main(String[] args) throws Exception {
        extractTarGz("path/to/archive.tar.gz", "/tmp/unpack");
    }

    private static void extractTarGz(String archivePath, String outputDir) throws Exception {
        Path tarGzFile = Paths.get(archivePath);
        Path destinationDir = Paths.get(outputDir);

        try (FileInputStream fis = new FileInputStream(tarGzFile.toFile());
             GZIPInputStream gzipInputStream = new GZIPInputStream(fis)) {

            byte[] buffer = new byte[1024];
            int length;

            while ((length = gzipInputStream.read(buffer)) > 0) {
                Path extractedFilePath = destinationDir.resolve("extracted_file");
                Files.createDirectories(extractedFilePath.getParent());
                try (FileOutputStream fos = new FileOutputStream(extractedFilePath.toFile())) {
                    fos.write(buffer, 0, length);
                }
            }
        }

        System.out.println("Archive extracted to: " + outputDir);
    }
}