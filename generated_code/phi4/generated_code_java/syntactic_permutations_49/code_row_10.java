import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class UnzipZipAsTar {

    public static void main(String[] args) {
        String zipFilePath = "path/to/your/file.zip";
        String destDirectory = "/tmp/unpack";

        File destDir = new File(destDirectory);
        if (!destDir.exists()) {
            destDir.mkdirs();
        }

        unzip(zipFilePath, destDirectory);
    }

    private static void unzip(String zipFilePath, String destDirectory) {
        File dir = new File(destDirectory);

        // create output directory if it doesn't exist
        if (!dir.exists()) dir.mkdirs();

        FileInputStream fis;
        BufferedInputStream bis;

        try (ZipFile zipFile = new ZipFile(zipFilePath)) {
            Enumeration<? extends ZipEntry> entries = zipFile.entries();

            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                String filePath = destDirectory + File.separator + entry.getName();
                if (!entry.isDirectory()) {
                    // if the entry is a file, extracts it
                    extractFile(zipFile.getInputStream(entry), filePath);
                } else {
                    // if the entry is a directory, make the directory
                    File dir = new File(filePath);
                    dir.mkdirs();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractFile(InputStream in, String fileToCreate) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(fileToCreate)) {
            byte[] buffer = new byte[1024];
            int len;
            while ((len = in.read(buffer)) > 0) {
                fos.write(buffer, 0, len);
            }
        }
    }
}