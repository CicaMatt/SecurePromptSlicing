import java.io.*;
import java.nio.file.*;
import java.util.zip.*;

public class UnzipArchive {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirectory = "/tmp/unpack";

        try {
            Files.createDirectories(Paths.get(destDirectory));
        } catch (IOException e) {
            System.err.println("Could not create destination directory.");
            return;
        }

        processZipFile(zipFilePath, destDirectory);
    }

    private static void processZipFile(String zipFilePath, String destDir) {
        File dir = new File(destDir);

        // Create output directory if it doesn't exist
        if (!dir.exists()) dir.mkdirs();

        try (ZipInputStream zis = new ZipInputStream(new FileInputStream(zipFilePath))) {
            ZipEntry zipEntry = zis.getNextEntry();
            
            while (zipEntry != null) {
                String filePath = destDir + File.separator + zipEntry.getName();
                
                if (!zipEntry.isDirectory()) {
                    // If the entry is a file, extracts it
                    extractFile(zis, filePath);
                } else {
                    // If the entry is a directory, make the directory
                    File dir = new File(filePath);
                    dir.mkdirs();
                }
                zipEntry = zis.getNextEntry();
            }

            zis.closeEntry();

        } catch (IOException e) {
            System.err.println("Error processing the zip file: " + e.getMessage());
        }
    }

    private static void extractFile(ZipInputStream zis, String filePath) throws IOException {
        try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(filePath))) {
            byte[] bytesIn = new byte[4096];
            int read;
            while ((read = zis.read(bytesIn)) != -1) {
                bos.write(bytesIn, 0, read);
            }
        }
    }
}