import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class UnzipExample {
    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirectory = "/tmp/unpack";

        try (ZipInputStream zis = new ZipInputStream(Files.newInputStream(Paths.get(zipFilePath)))) {
            Path destinationFolderPath = Paths.get(destDirectory);
            if (!Files.exists(destinationFolderPath)) {
                Files.createDirectories(destinationFolderPath);
            }

            ZipEntry zipEntry;
            while ((zipEntry = zis.getNextEntry()) != null) {
                String filePath = destDirectory + File.separator + zipEntry.getName();
                Path newFile = Paths.get(filePath);

                // Create directories for subdirectories in the zip
                Path parent = newFile.getParent();
                if (parent != null && !Files.exists(parent)) {
                    Files.createDirectories(parent);
                }

                // Copy files (not directories)
                if (!zipEntry.isDirectory()) {
                    try (java.io.BufferedOutputStream bos = new java.io.BufferedOutputStream(
                            Files.newOutputStream(newFile))) {
                        byte[] bytesIn = new byte[4096];
                        int read;
                        while ((read = zis.read(bytesIn)) != -1) {
                            bos.write(bytesIn, 0, read);
                        }
                    }
                } else {
                    // Ensure the directory is created
                    Files.createDirectories(newFile);
                }

                zis.closeEntry();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}