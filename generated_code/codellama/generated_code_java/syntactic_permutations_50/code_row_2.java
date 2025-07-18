import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.nio.charset.StandardCharsets;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class Unpacker {
    public static void main(String[] args) throws Exception {
        String zipPath = "archive.zip";  // path to the archive
        String destDir = "/tmp/unpack";   // directory where files will be extracted
        extractFilesFromZipTo(zipPath, destDir);
    }

    public static void extractFilesFromZipTo(String zipFilePath, String destinationDirectory) throws Exception {
        try (ZipFile zipFile = new ZipFile(zipFilePath)) {
            List<String> fileNames = new ArrayList<>();
            for (Enumeration<? extends ZipEntry> entries = zipFile.entries(); entries.hasMoreElements(); ) {
                String fileName = entries.nextElement().getName();
                if (!fileNames.contains(fileName)) {
                    fileNames.add(fileName);
                }
            }
            for (String fileName : fileNames) {
                extractFileFromZipTo(zipFilePath, destinationDirectory, fileName);
            }
        }
    }

    public static void extractFileFromZipTo(String zipFilePath, String destinationDirectory, String fileName) throws Exception {
        File directory = new File(destinationDirectory);
        if (!directory.exists()) {
            directory.mkdir();
        }
        try (InputStream inputStream = getInputStreamForFileInZip(zipFilePath, fileName)) {
            Files.copy(inputStream, Paths.get(destinationDirectory + "/" + fileName));
        }
    }

    public static InputStream getInputStreamForFileInZip(String zipFilePath, String fileName) throws Exception {
        try (ZipFile zipFile = new ZipFile(zipFilePath)) {
            ZipEntry entry = zipFile.getEntry(fileName);
            if (entry != null) {
                return zipFile.getInputStream(entry);
            }
        }
        return null;
    }
}