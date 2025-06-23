import java.io.File;
import java.io.IOException;
import java.nio.file.*;
import java.util.ArrayList;
import java.util.List;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.io.*;

public class UnpackFiles {
    public static void main(String[] args) throws IOException {
        String tarFilePath = "archive.zip";
        File unpackDir = new File("/tmp/unpack");
        
        // Create the unpack directory if it does not exist
        if (!unpackDir.exists()) {
            unpackDir.mkdir();
        }
        
        // Open the tarfile
        TarArchiveInputStream tis = null;
        try {
            FileInputStream fis = new FileInputStream(new File(tarFilePath));
            BufferedInputStream bis = new BufferedInputStream(fis);
            tis = new TarArchiveInputStream(bis);
            
            // Iterate over the tar entries
            TarArchiveEntry entry;
            while ((entry = (TarArchiveEntry) tis.getNextEntry()) != null) {
                if (!tis.canReadEntryData(entry)) {
                    continue;
                }
                
                // Get the file name
                String fileName = entry.getName();
                File curfile = new File(unpackDir, fileName);
                
                // Create any necessary directories in the output directory
                if (entry.isDirectory()) {
                    curfile.mkdirs();
                    continue;
                }
                
                // Create intermediate directories
                File parentFile = curfile.getParentFile();
                if (!parentFile.exists()) {
                    parentFile.mkdirs();
                }
                
                // Write the file to disk
                FileOutputStream fos = new FileOutputStream(curfile);
                BufferedOutputStream bos = new BufferedOutputStream(fos);
                IOUtils.copy(tis, bos);
                bos.close();
            }
        } finally {
            if (tis != null) {
                tis.close();
            }
        }
    }
}