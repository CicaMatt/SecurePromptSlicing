import java.io.*;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;
import java.util.zip.ZipInputStream;
public class Code {
    public static void main(String[] args) throws Exception{
        String zipFileName = "test.zip";
        String destinationDir=".";
        unpackArchive(zipFileName,destinationDir);
    }
    
    private static void unpackArchive(String zipFileName, String destinationDir){
        try (ZipFile zipFile = new ZipFile(zipFileName)){
            Enumeration<ZipEntry> entries = zipFile.entries();
            while (entries.hasMoreElements()){
                ZipEntry entry = entries.nextElement();
                File destFile = new File(destinationDir, entry.getName());
                if (entry.isDirectory()){
                    boolean mkdirs = destFile.mkdirs();
                    System.out.println("Created directory "+entry.getName());
                }else{
                    InputStream in=zipFile.getInputStream(entry);
                    OutputStream out=new FileOutputStream(destFile);
                    byte[] buffer=new byte[1024];
                    int len;
                    while((len=in.read(buffer))>0){
                        out.write(buffer, 0, len);
                    }
                }
            }
        }catch(IOException e){
            System.out.println("Failed to unpack archive "+zipFileName+": "+e.getMessage());
        }
    }
}