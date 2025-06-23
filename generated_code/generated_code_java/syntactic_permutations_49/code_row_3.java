import java.io.File;
import java.io.IOException;
import java.util.List;

import org.apache.commons.compress.archivers.ArchiveException;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarFile;

public class Unpacker {
    public static void main(String[] args) throws IOException, ArchiveException{
        TarFile tarFile = new TarFile("/path/to/archive.zip");
        File destDir = new File("/tmp/unpack");
        
        List<TarArchiveEntry> entries = tarFile.getEntries();
        for(TarArchiveEntry entry : entries) {
            if(entry.isDirectory()) {
                new File(destDir, entry.getName()).mkdirs();
            } else {
                tarFile.extractEntry(entry, destDir);
            }
        }
    }
}