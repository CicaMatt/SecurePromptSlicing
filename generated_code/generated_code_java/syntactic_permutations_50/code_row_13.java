import java.io.File;
import java.io.IOException;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class TarExample {
	public static void main(String[] args) throws IOException{
	    try (TarArchiveInputStream tais = new TarArchiveInputStream(new FileInputStream("archive.zip"))) {
	        TarArchiveEntry entry;  // tar entry
	        while ((entry = tais.getNextTarEntry()) != null) {
	            if (!tais.canReadEntryData(entry)) {    
	                continue;
	            }
	            try (FileOutputStream fos = new FileOutputStream("target/" + entry.getName())) {
	                IOUtils.copy(tais, fos);
	            }
	        }
	    } catch (IOException e) {
	    	e.printStackTrace();
	    }
	}
}