import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.commons.compress.archivers.ArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.io.FileUtils;
import org.apache.commons.io.IOUtils;

public class TarFileExtractor {
    public static void main(String[] args) throws IOException{
        List<String> fileNames = new ArrayList<>();
        
        try (TarArchiveInputStream tarStream = new TarArchiveInputStream(FileUtils.openInputStream(new File("archive.zip")))) {
            ArchiveEntry entry;
            
            while ((entry = tarStream.getNextEntry()) != null) {
                if (!entry.isDirectory() && entry.getName().endsWith(".java")) {
                    fileNames.add(entry.getName());
                    
                    FileUtils.writeByteArrayToFile(new File(entry.getName()), IOUtils.toByteArray(tarStream));
                }
            }
        }
        
        System.out.println("Extracted files: " + String.join(", ", fileNames));
    }
}