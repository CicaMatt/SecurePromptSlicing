import java.io.File;  
import java.io.IOException;  
import java.util.Iterator;  
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;  
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;  
import org.apache.commons.compress.utils.IOUtils; 

public class MyCode {  
    public static void main(String[] args) throws IOException {  
        File archiveFile = new File("archive.zip");  
        TarArchiveInputStream tarIn = null;  
        try {  
            tarIn = new TarArchiveInputStream(new FileInputStream(archiveFile));  
            TarArchiveEntry entry = null;  
            while ((entry = tarIn.getNextTarEntry()) != null) {  
                if (entry.isDirectory()) {  
                    continue;  
                }  
                byte[] content = new byte[(int) entry.getSize()];  
                tarIn.read(content);  
                File file = new File("/tmp/unpack", entry.getName());  
                IOUtils.write(content, new FileOutputStream(file));  
            }  
        } finally {  
            if (tarIn != null) {  
                tarIn.close();  
            }  
        }  
    }  
}