import java.io.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;
import java.util.zip.ZipInputStream;

public class UnzipArchive {
    public static void main(String args[]) throws Exception {
        String archiveFileName = "archive.zip";

        // Create a ZipFile object for the archive.zip file
        ZipFile zipFile = new ZipFile(archiveFileName);
        
        FileInputStream fis = new FileInputStream(archiveFileName);
        ZipInputStream zis = new ZipInputStream(fis);
        ZipEntry entry;

        while ((entry = zis.getNextEntry()) != null) {
            // Write the file to disk
            OutputStream os = new FileOutputStream(entry.getName());
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = zis.read(buffer)) != -1) {
                os.write(buffer, 0, bytesRead);
            }
            // Close the streams
            os.close();
        }
        zis.closeEntry();
        zis.close();
    }
}