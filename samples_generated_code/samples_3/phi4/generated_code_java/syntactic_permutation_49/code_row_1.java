import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class UnzipToTemp {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirectory = "/tmp/unpack";

        unzip(zipFilePath, destDirectory);
    }

    private static void unzip(String zipFilePath, String destDir) {
        File dir = new File(destDir);
        // create output directory if it doesn't exist
        if (!dir.exists()) dir.mkdirs();

        try (ZipFile zipFile = new ZipFile(zipFilePath)) {
            Enumeration<? extends ZipEntry> entries = zipFile.entries();
            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                File destFile = new File(dir, entry.getName());

                if (!entry.isDirectory()) {
                    // If the entry is a file, extracts it
                    extractFile(zipFile, entry, destFile);
                } else {
                    // If the entry is a directory, make the directory
                    destFile.mkdirs();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractFile(ZipFile zipFile, ZipEntry entry, File destFile)
            throws IOException {
        try (
            BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(destFile));
            FileInputStream fis = new FileInputStream(zipFile.getInputStream(entry))
        ) {
            byte[] buffer = new byte[1024];
            int len;
            while ((len = fis.read(buffer)) > 0) {
                bos.write(buffer, 0, len);
            }
        }
    }
}