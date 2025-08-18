import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class UnzipArchive {
    public static void main(String[] args) {
        String sourceZipFile = "archive.zip";
        String destinationDirectory = "/tmp/unpack";

        File destDir = new File(destinationDirectory);
        if (!destDir.exists()) {
            destDir.mkdir();
        }

        unzip(sourceZipFile, destinationDirectory);
    }

    private static void unzip(String zipFilePath, String destDirectory) {
        File dir = new File(destDirectory);
        // Create output directory if it doesn't exist
        if (!dir.exists()) {
            dir.mkdirs();
        }
        
        try (ZipInputStream zis = new ZipInputStream(Files.newInputStream(Paths.get(zipFilePath)))) {
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
        BufferedOutputStream bos = new BufferedOutputStream(Files.newOutputStream(Paths.get(filePath)));
        byte[] bytesIn = new byte[4096];
        int read = 0;
        
        while ((read = zis.read(bytesIn)) != -1) {
            bos.write(bytesIn, 0, read);
        }
        
        bos.close();
    }
}