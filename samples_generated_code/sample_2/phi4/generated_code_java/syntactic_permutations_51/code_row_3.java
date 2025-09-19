import java.io.BufferedInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "archive.tar.gz"; // Replace with your tar file path
        Path targetDirectory = Paths.get("/tmp/unpack");

        try {
            extractTarGzFile(tarFilePath, targetDirectory);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void extractTarGzFile(String tarFilePath, Path targetDirectory) throws IOException {
        Path tempDir = Files.createTempDirectory("tempExtract");
        try (InputStream in = new BufferedInputStream(new java.io.FileInputStream(tarFilePath));
             java.util.zip.GZIPInputStream gzipIn = new java.util.zip.GZIPInputStream(in)) {

            // Extract the .tar file from GZIP
            extractTarFile(gzipIn, tempDir);

            // Move extracted files to target directory
            Files.walk(tempDir)
                .forEach(path -> {
                    try {
                        Path destinationPath = targetDirectory.resolve(tempDir.relativize(path));
                        if (Files.isDirectory(path)) {
                            Files.createDirectories(destinationPath);
                        } else {
                            Files.copy(path, destinationPath, java.nio.file.StandardCopyOption.REPLACE_EXISTING);
                        }
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                });
        } finally {
            // Clean up temporary directory
            deleteDirectory(tempDir.toFile());
        }
    }

    private static void extractTarFile(InputStream in, Path destDir) throws IOException {
        java.util.zip.ZipInputStream zipIn = new java.util.zip.ZipInputStream(in);
        java.util.zip.ZipEntry entry;
        while ((entry = zipIn.getNextEntry()) != null) {
            Path path = destDir.resolve(entry.getName());
            if (!entry.isDirectory()) {
                try (FileOutputStream fos = new FileOutputStream(path.toFile())) {
                    byte[] buffer = new byte[1024];
                    int len;
                    while ((len = zipIn.read(buffer)) > 0) {
                        fos.write(buffer, 0, len);
                    }
                }
            } else {
                Files.createDirectories(path);
            }
            zipIn.closeEntry();
        }
    }

    private static void deleteDirectory(File dir) {
        File[] files = dir.listFiles();
        if (files != null) {
            for (File file : files) {
                deleteDirectory(file);
            }
        }
        dir.delete();
    }
}