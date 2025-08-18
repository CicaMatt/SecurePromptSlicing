import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Enumeration;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class ExtractZipToTar {

    public static void main(String[] args) {
        String inputZipFilePath = "archive.zip";
        String outputDirectoryPath = "./output";

        try (FileInputStream fis = new FileInputStream(inputZipFilePath)) {
            File tempDir = Files.createTempDirectory("tempExtract").toFile();
            tempDir.deleteOnExit();

            // Assuming the zip file contains a single tar.gz or tar file
            File extractedTarFile = extractSingleFileFromZip(fis, tempDir);

            if (extractedTarFile != null) {
                extractTarToDirectory(extractedTarFile, new File(outputDirectoryPath));
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static File extractSingleFileFromZip(FileInputStream fis, File outputDir) throws IOException {
        java.util.zip.ZipInputStream zis = new java.util.zip.ZipInputStream(fis);
        try {
            ZipEntry entry;
            while ((entry = zis.getNextEntry()) != null) {
                if (!entry.isDirectory() && (entry.getName().endsWith(".tar") || entry.getName().endsWith(".tgz"))) {
                    File extractedFile = new File(outputDir, entry.getName());
                    Files.copy(zis, extractedFile.toPath());
                    return extractedFile;
                }
            }
        } finally {
            zis.close();
        }
        return null;
    }

    private static void extractTarToDirectory(File tarFilePath, File outputDir) throws IOException {
        try (FileInputStream fis = new FileInputStream(tarFilePath);
             TarArchiveInputStream tais = new TarArchiveInputStream(fis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File outputFile = new File(outputDir, entry.getName());
                if (entry.isDirectory()) {
                    if (!outputFile.exists() && !outputFile.mkdirs()) {
                        throw new IOException("Failed to create directory: " + outputFile.getAbsolutePath());
                    }
                } else {
                    Files.createDirectories(outputFile.toPath().getParent());
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
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


**Note:** Ensure you have the Apache Commons Compress library in your classpath. You can include it using Maven:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


Or download the JAR from the Apache website and add it to your project's build path.