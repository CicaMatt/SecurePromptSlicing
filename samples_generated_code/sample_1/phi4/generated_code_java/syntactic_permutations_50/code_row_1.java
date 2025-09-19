import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class ArchiveExtractor {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        File destDir = new File("extracted_files");
        
        if (!destDir.exists()) {
            destDir.mkdir();
        }

        unzip(zipFilePath, destDir);
    }
    
    private static void unzip(String zipFilePath, File destinationDir) {
        try (ZipInputStream zis = new ZipInputStream(new FileInputStream(zipFilePath))) {
            ZipEntry zipEntry = zis.getNextEntry();

            while (zipEntry != null) {
                String fileName = zipEntry.getName();
                File newFile = new File(destinationDir, fileName);
                
                if (!zipEntry.isDirectory()) {
                    // If the entry is a file, extracts it
                    extractFile(zis, newFile);
                } else {
                    // If the entry is a directory, make the directory
                    newFile.mkdirs();
                }
                zipEntry = zis.getNextEntry();
            }

            zis.closeEntry();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractFile(ZipInputStream zis, File destination) throws IOException {
        try (
            FileOutputStream fos = new FileOutputStream(destination);
        ) {
            byte[] buffer = new byte[1024];
            int len;
            
            while ((len = zis.read(buffer)) > 0) {
                fos.write(buffer, 0, len);
            }
        }
    }
}
