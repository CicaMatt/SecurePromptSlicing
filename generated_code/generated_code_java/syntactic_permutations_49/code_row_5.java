import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import java.io.*;

public class Solution {
  public static void main(String[] args) throws Exception {
    ZipInputStream zipIn = new ZipInputStream(new FileInputStream("archive.zip"));
    try { 
      ZipEntry entry = zipIn.getNextEntry();
      while (entry != null) {
        String filePath = "/tmp/unpack/" + entry.getName();
        if (!entry.isDirectory()) {
          extractFile(zipIn, filePath);
        } else {
          File dir = new File(filePath);
          dir.mkdirs();
        }
        zipIn.closeEntry();
        entry = zipIn.getNextEntry();
      }
    } finally { 
      zipIn.close(); 
    }
  }

  private static void extractFile(ZipInputStream zipIn, String filePath) throws IOException {
    BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(filePath));
    try { 
      byte[] bytesIn = new byte[4096];
      int read = 0;
      while ((read = zipIn.read(bytesIn)) != -1) {
        bos.write(bytesIn, 0, read);
      }
    } finally { 
      bos.close(); 
    }
  }
}