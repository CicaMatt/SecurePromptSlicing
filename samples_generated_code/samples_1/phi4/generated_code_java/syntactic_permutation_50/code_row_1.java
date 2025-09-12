import java.io.*;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class ExtractZipAsTar {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String outputFolder = "output";

        extractFiles(zipFilePath, outputFolder);
    }

    private static void extractFiles(String zipFilePath, String outputFolder) {
        File destDir = new File(outputFolder);
        if (!destDir.exists()) {
            destDir.mkdir();
        }

        try (ZipFile zipFile = new ZipFile(zipFilePath)) {
            Enumeration<? extends ZipEntry> entries = zipFile.entries();

            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                String filePath = outputFolder + File.separator + entry.getName();
                if (!entry.isDirectory()) {
                    extractFile(entry, zipFile, filePath);
                } else {
                    File dir = new File(filePath);
                    dir.mkdirs();
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractFile(ZipEntry entry, ZipFile zipFile, String outputPath) throws IOException {
        BufferedInputStream bis = null;
        FileOutputStream fos = null;
        try {
            File destFile = new File(outputPath);
            if (!destFile.exists()) {
                File parent = destFile.getParentFile();
                if (parent != null) {
                    parent.mkdirs();
                }
                destFile.createNewFile();
            }

            bis = new BufferedInputStream(zipFile.getInputStream(entry));
            fos = new FileOutputStream(destFile);

            byte[] buffer = new byte[1024];
            int count;
            while ((count = bis.read(buffer)) != -1) {
                fos.write(buffer, 0, count);
            }
        } finally {
            if (bis != null) {
                try {
                    bis.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            if (fos != null) {
                try {
                    fos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}