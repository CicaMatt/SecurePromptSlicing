import java.io.*;
import java.nio.file.*;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class ExtractZipArchive {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirectory = "extracted_files";

        extractAll(zipFilePath, destDirectory);
    }

    private static void extractAll(String zipFilePath, String destDirectory) {
        File dir = new File(destDirectory);
        // Create output directory if it doesn't exist
        if (!dir.exists()) {
            dir.mkdirs();
        }
        
        try (ZipFile zipFile = new ZipFile(zipFilePath)) {
            Enumeration<? extends ZipEntry> entries = zipFile.entries();

            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                File outputFile = new File(dir, entry.getName());
                
                if (!entry.isDirectory() && !outputFile.exists()) {
                    // Create parent directories for the file
                    File parentDir = outputFile.getParentFile();
                    if (parentDir != null) {
                        parentDir.mkdirs();
                    }

                    try (InputStream in = zipFile.getInputStream(entry);
                         OutputStream out = new FileOutputStream(outputFile)) {

                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = in.read(buffer)) > 0) {
                            out.write(buffer, 0, len);
                        }
                    } catch (IOException e) {
                        System.out.println("Error extracting file: " + entry.getName());
                        e.printStackTrace();
                    }
                }
            }
        } catch (IOException e) {
            System.out.println("Error processing zip file");
            e.printStackTrace();
        }
    }
}