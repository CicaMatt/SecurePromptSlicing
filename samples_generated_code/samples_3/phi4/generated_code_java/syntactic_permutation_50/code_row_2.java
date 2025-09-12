import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class ZipExtractor {
    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirectoryPath = "/tmp/unpack";

        File destDir = new File(destDirectoryPath);
        if (!destDir.exists()) {
            boolean mkdirsSuccess = destDir.mkdirs();
            if (!mkdirsSuccess) {
                System.err.println("Failed to create directory: " + destDirectoryPath);
                return;
            }
        }

        extractFilesFromZip(zipFilePath, destDirectoryPath);
    }

    private static void extractFilesFromZip(String zipFilePath, String destDirectoryPath) {
        File dir = new File(destDirectoryPath);

        // Create output directory if it doesn't exist
        if (!dir.exists()) dir.mkdirs();

        try (FileInputStream fis = new FileInputStream(zipFilePath);
             ZipInputStream zis = new ZipInputStream(fis)) {

            ZipEntry zipEntry = zis.getNextEntry();
            while (zipEntry != null) {
                File newFile = newFile(dir, zipEntry);

                if (zipEntry.isDirectory()) {
                    if (!newFile.mkdirs() && !newFile.exists()) {
                        throw new IOException("Failed to create directory " + newFile);
                    }
                } else {
                    // Fix for Windows-created archives
                    File parent = newFile.getParentFile();
                    if (!parent.exists() && !parent.mkdirs()) {
                        throw new IOException("Failed to create directory " + parent);
                    }

                    // Write file content
                    try (FileOutputStream fos = new FileOutputStream(newFile)) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = zis.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
                zipEntry = zis.getNextEntry();
            }

            // Close the last entry
            zis.closeEntry();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static File newFile(File destinationDir, ZipEntry zipEntry) throws IOException {
        File destFile = new File(destinationDir, zipEntry.getName());

        String destDirPath = destinationDir.getCanonicalPath();
        String destFilePath = destFile.getCanonicalPath();

        if (!destFilePath.startsWith(destDirPath + File.separator)) {
            throw new IOException("Entry is outside of the target dir: " + zipEntry.getName());
        }

        return destFile;
    }
}