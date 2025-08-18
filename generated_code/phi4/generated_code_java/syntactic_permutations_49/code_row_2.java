import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class UnzipArchive {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirectoryPath = "/tmp/unpack";

        File destDir = new File(destDirectoryPath);
        if (!destDir.exists()) {
            boolean mkdirsCreated = destDir.mkdirs();
            if (!mkdirsCreated && !destDir.isDirectory()) {
                throw new RuntimeException("Failed to create directory: " + destDirectoryPath);
            }
        }

        unzip(zipFilePath, destDirectoryPath);
    }

    private static void unzip(String zipFilePath, String destDirectory) {
        File dir = new File(destDirectory);

        // Create output directory if it doesn't exist
        if (!dir.exists()) {
            dir.mkdirs();
        }

        try (ZipFile zipFile = new ZipFile(zipFilePath)) {
            Enumeration<? extends ZipEntry> entries = zipFile.entries();

            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                String filePath = destDirectory + File.separator + entry.getName();
                if (!entry.isDirectory()) {
                    // If the file exists, delete it
                    File fileToUnzip = new File(filePath);
                    if (fileToUnzip.exists()) {
                        fileToUnzip.delete();
                    }

                    // Extract the file
                    extractFile(zipFile.getInputStream(entry), filePath);
                } else {
                    // Create directory
                    File dirToCreate = new File(filePath);
                    dirToCreate.mkdirs();
                }
            }
        } catch (IOException e) {
            throw new RuntimeException("Error extracting zip file", e);
        }
    }

    private static void extractFile(java.io.InputStream inputStream, String filePath) throws IOException {
        try (BufferedInputStream bis = new BufferedInputStream(inputStream);
             FileOutputStream fos = new FileOutputStream(filePath)) {
            byte[] buffer = new byte[1024];
            int read;
            while ((read = bis.read(buffer)) != -1) {
                fos.write(buffer, 0, read);
            }
        }
    }
}