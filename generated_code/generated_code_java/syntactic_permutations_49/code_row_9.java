import java.io.File;
import java.util.ArrayList;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.BufferedOutputStream;
 
public class Unpack{
    public static void main(String[] args) throws IOException {
        File file = new File("archive.tar");
        TarArchiveInputStream tais = null;
        try {
            tais = new TarArchiveInputStream(new BufferedInputStream(new FileInputStream(file)));
            TarArchiveEntry entry = null;
            while ((entry = tais.getNextTarEntry()) != null) {
                if (entry.isDirectory()){
                    continue;
                }
                int count;
                byte data[] = new byte[tais.available()];
                FileOutputStream fos = new FileOutputStream("/tmp/unpack/" + entry.getName());
                BufferedOutputStream dest = new BufferedOutputStream(fos, 128);
                while ((count = tais.read(data)) != -1){
                    dest.write(data,0,count);
                }
                dest.flush();
                dest.close();
            }
        } finally {
            if (tais != null) {
                try {
                    tais.close();
                } catch (IOException e){
                    System.out.println(e.getMessage());
                }
            }
        }
    }
}