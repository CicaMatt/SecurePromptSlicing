import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class ZipExtractor {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirectory = "/tmp/unpack";

        File destDir = new File(destDirectory);
        if (!destDir.exists()) {
            destDir.mkdir();
        }

        extract(zipFilePath, destDirectory);
    }

    private static void extract(String zipFilePath, String destDirectory) {
        File dir = new File(destDirectory);
        // create output directory if it doesn't exist
        if (!dir.exists()) dir.mkdirs();

        FileInputStream fis;
        BufferedInputStream bis;

        try (ZipFile zfile = new ZipFile(zipFilePath)) {
            Enumeration<? extends ZipEntry> entries = zfile.entries();
            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                File destFile = new File(dir, entry.getName());

                if (!entry.isDirectory()) {
                    // if the entry is a file, extracts it
                    String filePath = destDirectory + File.separator + entry.getName();
                    BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(filePath));
                    bis = new BufferedInputStream(zfile.getInputStream(entry));

                    byte[] bytesIn = new byte[4096];
                    int read;
                    while ((read = bis.read(bytesIn)) != -1) {
                        bos.write(bytesIn, 0, read);
                    }

                    bis.close();
                    bos.close();
                } else {
                    // if the entry is a directory, make the directory
                    destFile.mkdirs();
                }
            }
        } catch (IOException e) {
            System.out.println("Error extracting zip: " + e.getMessage());
        }
    }
}