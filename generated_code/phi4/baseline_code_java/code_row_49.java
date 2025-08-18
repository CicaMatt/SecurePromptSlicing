import java.io.*;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class UnzipToDirectory {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirPath = "/tmp/unpack";

        unzip(zipFilePath, destDirPath);
    }

    private static void unzip(String zipFilePath, String destDirPath) {
        File dir = new File(destDirPath);
        if (!dir.exists()) {
            dir.mkdirs();
        }
        
        try (ZipFile zipFile = new ZipFile(zipFilePath)) {
            Enumeration<? extends ZipEntry> entries = zipFile.entries();

            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                String filePath = destDirPath + File.separator + entry.getName();
                
                if (!entry.isDirectory()) {
                    extractFile(zipFile, entry, filePath);
                } else {
                    File dir = new File(filePath);
                    dir.mkdirs();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractFile(ZipFile zipFile, ZipEntry entry, String filePath)
            throws IOException {
        BufferedInputStream bis = null;
        FileOutputStream fos = null;
        File parentDir = new File(filePath).getParentFile();

        if (!parentDir.exists()) {
            parentDir.mkdirs();
        }

        try {
            fos = new FileOutputStream(filePath);
            bis = new BufferedInputStream(zipFile.getInputStream(entry));

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