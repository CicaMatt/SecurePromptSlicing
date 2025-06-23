import java.io.*;
import java.util.zip.*;

public class Unzip {
    public static void main(String[] args) throws IOException {
        // unzip files into /tmp/unpack directory
        String zipFilePath = "/home/user/archive.zip";
        String destDirectory = "/tmp/unpack/";
        byte[] buffer = new byte[1024];

        ZipInputStream zis = new ZipInputStream(new FileInputStream(zipFilePath));
        ZipEntry zipEntry = zis.getNextEntry();
        while (zipEntry != null) {
            File newFile = new File(destDirectory + zipEntry.getName());
            FileOutputStream fos = new FileOutputStream(newFile);
            int len;
            while ((len = zis.read(buffer)) > 0) {
                fos.write(buffer, 0, len);
            }
            fos.close();
            zipEntry = zis.getNextEntry();
        }
        zis.closeEntry();
        zis.close();
    }
}