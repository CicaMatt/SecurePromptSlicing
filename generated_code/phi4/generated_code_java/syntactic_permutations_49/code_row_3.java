import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class UnzipToDirectory {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirPath = "/tmp/unpack";

        File destDir = new File(destDirPath);
        if (!destDir.exists()) {
            boolean mkdirsCreated = destDir.mkdirs();
            if (!mkdirsCreated) {
                System.err.println("Could not create directory: " + destDirPath);
                return;
            }
        }

        unzip(zipFilePath, destDirPath);
    }

    private static void unzip(String zipFilePath, String destDirectory) {
        File dir = new File(destDirectory);

        // Create output directory if it doesn't exist
        if (!dir.exists()) dir.mkdirs();

        byte[] buffer = new byte[1024];

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
                zis.closeEntry();
                zipEntry = zis.getNextEntry();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractFile(ZipInputStream zis, String filePath) throws IOException {
        BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(filePath));

        int read;
        while ((read = zis.read(buffer)) != -1) {
            bos.write(buffer, 0, read);
        }

        bos.close();
    }
}