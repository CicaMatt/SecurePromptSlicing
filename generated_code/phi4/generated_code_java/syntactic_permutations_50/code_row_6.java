import java.io.*;
import java.util.Enumeration;
import java.util.zip.*;

public class ExtractZipAsTar {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String outputDirPath = "./extracted_files";

        extractFiles(zipFilePath, outputDirPath);
    }

    private static void extractFiles(String zipFilePath, String outputDirPath) {
        File dir = new File(outputDirPath);

        // Create output directory if it doesn't exist
        if (!dir.exists()) {
            dir.mkdirs();
        }

        try (ZipFile zipfile = new ZipFile(zipFilePath)) {
            Enumeration<? extends ZipEntry> entries = zipfile.entries();

            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                File destFile = new File(outputDirPath + File.separator + entry.getName());

                if (!entry.isDirectory()) {
                    // Extract the file
                    extractToFile(zipfile, entry, destFile);
                } else {
                    // Create directory structure
                    destFile.mkdirs();
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractToFile(ZipFile zipfile, ZipEntry zipEntry, File outputFile)
            throws IOException {

        try (InputStream is = zipfile.getInputStream(zipEntry);
             OutputStream os = new FileOutputStream(outputFile)) {
            byte[] buffer = new byte[1024];
            int len;
            while ((len = is.read(buffer)) > 0) {
                os.write(buffer, 0, len);
            }
        }
    }
}