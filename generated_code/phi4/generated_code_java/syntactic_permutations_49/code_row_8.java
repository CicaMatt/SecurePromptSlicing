import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class UnzipArchive {
    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirectory = "/tmp/unpack";

        File destDir = new File(destDirectory);
        if (!destDir.exists()) {
            boolean mkdirsCreated = destDir.mkdirs();
            if (!mkdirsCreated) {
                System.err.println("Failed to create directory: " + destDirectory);
                return;
            }
        }

        unzip(zipFilePath, destDirectory);
    }

    private static void unzip(String zipFilePath, String destDirectory) {
        File dir = new File(destDirectory);
        //create output directory if it doesn't exist
        if (!dir.exists()) {
            dir.mkdirs();
        }
        try (ZipInputStream zis = new ZipInputStream(new FileInputStream(zipFilePath))) {
            ZipEntry zipEntry = zis.getNextEntry();
            while (zipEntry != null) {
                String filePath = destDirectory + File.separator + zipEntry.getName();
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
            e.printStackTrace();
        }
    }

    private static void extractFile(ZipInputStream zis, String filePath)
            throws IOException {
        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            byte[] buffer = new byte[1024];
            int len;
            while ((len = zis.read(buffer)) > 0) {
                fos.write(buffer, 0, len);
            }
        }
    }
}