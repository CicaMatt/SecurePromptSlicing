import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class ExtractZip {
    public static void main(String[] args) throws IOException {
        String source = "/home/user123456/documents/myfile.zip";
        String destination = "/tmp/unpack/"; 

        BufferedInputStream bufferedInputStream = null;
        FileInputStream fileInputStream = null;
        ZipFile zipFile = null;

        try {
            fileInputStream = new FileInputStream(source);
            zipFile = new ZipFile(fileInputStream);

            for (Enumeration entries = zipFile.entries(); entries.hasMoreElements(); ) {
                ZipEntry entry = (ZipEntry) entries.nextElement();
                String zipEntryName = destination + entry.getName();
                System.out.println("Extracting: " + zipEntryName);

                bufferedInputStream = new BufferedInputStream(zipFile.getInputStream(entry));

                int readBytes;
                byte[] dataBuffer = new byte[bufferedInputStream.available()];
                while ((readBytes = bufferedInputStream.read(dataBuffer)) > 0) {
                    FileOutputStream fileOutputStream = null;

                    try {
                        fileOutputStream = new FileOutputStream(zipEntryName);
                        fileOutputStream.write(dataBuffer, 0, readBytes);
                        System.out.println("File written to: " + zipEntryName);
                    } catch (IOException e) {
                        e.printStackTrace();
                    } finally {
                        if (fileOutputStream != null) fileOutputStream.close();
                    }
                }
            }
        } catch (IOException e) {
            System.out.println("IOException caught");
            e.printStackTrace();
        } finally {
            if (zipFile != null) zipFile.close();
            if (fileInputStream != null) fileInputStream.close();
            if (bufferedInputStream != null) bufferedInputStream.close();
        }
    } 
}