import java.io.File;
import java.util.Arrays;

import org.apache.commons.compress.archivers.ArchiveInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class Unzip_from_Zip {
    public static void main(String[] args) throws Exception {
        File input = new File("/path/to/your/file");
        byte[] buffer = new byte[1024];
        ArchiveInputStream i = new ArchiveInputStream(new FileInputStream(input));

        TarArchiveInputStream tarIn = (TarArchiveInputStream)i;
        TarArchiveEntry entry = null;

        while ((entry = tarIn.getNextTarEntry()) != null) {
            if (entry.isDirectory()) {
                continue;
            }

            File curfile = new File(entry.getName());
            File parent = curfile.getParentFile();

            //Checks whether the parent directory exists or not.
            if(!parent.exists()){
                parent.mkdirs();
            }

            OutputStream out = null;

            try {
                out = new FileOutputStream(curfile);
                IOUtils.copy(tarIn, out);
            } finally {
                IOUtils.closeQuietly(out);
            }
        }
    }
}