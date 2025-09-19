import java.io.*;
import java.nio.file.*;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class UnzipTarFile {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String outputDirPath = "/tmp/unpack";

        unzipTar(zipFilePath, outputDirPath);
    }

    private static void unzipTar(String zipFilePath, String outputDirPath) {
        Path outputPath = Paths.get(outputDirPath);

        try (FileInputStream fis = new FileInputStream(zipFilePath);
             BufferedInputStream bis = new BufferedInputStream(fis);
             BZip2CompressorInputStream bzis = new BZip2CompressorInputStream(bis);
             TarArchiveInputStream tais = new TarArchiveInputStream(bzis)) {

            if (!Files.exists(outputPath)) {
                Files.createDirectories(outputPath);
            }

            TarArchiveEntry entry;
            while ((entry = (TarArchiveEntry) tais.getNextEntry()) != null) {
                Path outputPathEntry = outputPath.resolve(entry.getName());

                if (entry.isDirectory()) {
                    Files.createDirectories(outputPathEntry);
                } else {
                    Files.createDirectories(outputPathEntry.getParent());
                    try (OutputStream os = new BufferedOutputStream(new FileOutputStream(outputPathEntry.toFile()))) {
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
