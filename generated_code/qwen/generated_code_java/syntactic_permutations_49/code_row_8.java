import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class UnzipArchive {
    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirectory = "/tmp/unpack";

        try (FileInputStream fis = new FileInputStream(zipFilePath);
             ZipInputStream zis = new ZipInputStream(fis)) {

            byte[] buffer = new byte[1024];
            ZipEntry zipEntry = zis.getNextEntry();
            while (zipEntry != null) {
                String filePath = destDirectory + File.separator + zipEntry.getName();

                if (!zipEntry.isDirectory()) {
                    extractFile(zis, filePath, buffer);
                } else {
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

    private static void extractFile(ZipInputStream zis, String filePath, byte[] buffer) throws IOException {
        File newFile = new File(filePath);

        // fix for Windows-created archives
        String parent = newFile.getParent();
        if (parent != null) {
            File parentDir = new File(parent);
            if (!parentDir.mkdirs() && !parentDir.isDirectory()) {
                throw new IOException("Failed to create directory " + parentDir);
            }
        }

        try (FileOutputStream fos = new FileOutputStream(newFile)) {
            int len;
            while ((len = zis.read(buffer)) > 0) {
                fos.write(buffer, 0, len);
            }
        }
    }
}