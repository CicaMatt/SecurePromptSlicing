import java.io.*;
import java.nio.file.*;
import java.util.zip.*;

public class UnzipZipToTmpDirectory {
    public static void main(String[] args) throws IOException {
        String zipFilePath = "archive.zip";
        Path targetDirPath = Paths.get("/tmp/unpack");

        // Create the target directory if it doesn't exist
        Files.createDirectories(targetDirPath);

        // Open the ZIP file and iterate through its entries
        try (ZipInputStream zis = new ZipInputStream(new FileInputStream(zipFilePath))) {
            ZipEntry entry;
            while ((entry = zis.getNextEntry()) != null) {
                Path filePath = targetDirPath.resolve(entry.getName());
                
                if (!entry.isDirectory()) {
                    // Extract the file data to a specific path
                    Files.createDirectories(filePath.getParent());
                    try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(filePath.toFile()))) {
                        byte[] bytesIn = new byte[4096];
                        int read;
                        while ((read = zis.read(bytesIn)) != -1) {
                            bos.write(bytesIn, 0, read);
                        }
                    }
                } else {
                    // If it's a directory, make sure the path exists
                    Files.createDirectories(filePath);
                }

                zis.closeEntry();
            }
        }
    }
}