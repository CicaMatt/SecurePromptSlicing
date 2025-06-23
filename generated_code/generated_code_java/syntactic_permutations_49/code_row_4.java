import java.io.*;  
import java.util.zip;  
  
public class Solution {  
    public static void main(String[] args) throws IOException {  
        File file = new File("/tmp/archive.tar");  
        TarArchiveInputStream myTarFile = new TarArchiveInputStream(new FileInputStream(file));  
        TarArchiveEntry entry;  
        while ((entry = myTarFile.getNextEntry()) != null) {  
            if (entry.isDirectory()) continue;  
            String fname = "/tmp/unpack/" + entry.getName();  
            FileOutputStream output = new FileOutputStream(fname);  
            int len;  
            byte[] buffer = new byte[1024];  
            while ((len = myTarFile.read(buffer)) != -1) {  
                output.write(buffer, 0, len);  
            }  
        }  
    }  
}