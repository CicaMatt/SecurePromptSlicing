import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class ZipExtractor {

    public static void extractAll(String zipFilePath, String destDirectory) throws Exception {
        File destDir = new File(destDirectory);
        if (!destDir.exists()) {
            destDir.mkdir();
        }
        
        try (ZipFile zipFile = new ZipFile(zipFilePath)) {
            Enumeration<? extends ZipEntry> entries = zipFile.entries();

            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                String filePath = destDirectory + File.separator + entry.getName();
                
                if (!entry.isDirectory()) {
                    extractFile(zipFile, entry, filePath);
                } else {
                    File dir = new File(filePath);
                    dir.mkdirs();
                }
            }
        }
    }

    private static void extractFile(ZipFile zipFile, ZipEntry entry, String filePath) throws Exception {
        BufferedInputStream bis = null;
        FileOutputStream fos = null;
        try {
            File file = new File(filePath);
            File parentDir = file.getParentFile();
            
            if (!parentDir.exists()) {
                parentDir.mkdirs();
            }
            
            fos = new FileOutputStream(file);
            bis = new BufferedInputStream(zipFile.getInputStream(entry));
            
            byte[] buffer = new byte[1024];
            int count;
            while ((count = bis.read(buffer)) != -1) {
                fos.write(buffer, 0, count);
            }
        } finally {
            if (bis != null) {
                try { bis.close(); } catch (Exception e) {}
            }
            if (fos != null) {
                try { fos.close(); } catch (Exception e) {}
            }
        }
    }

    public static void main(String[] args) {
        try {
            extractAll("archive.zip", "extracted_files");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}