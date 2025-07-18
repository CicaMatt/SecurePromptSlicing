import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.util.Enumeration;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.ArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class Main {
    public static void main(String[] args) throws Exception {
        String file = "/path/to/your/file";
        InputStream is = new FileInputStream(file);
        ReadableByteChannel rbc = Channels.newChannel(is);
        BufferedReader br = new BufferedReader(new InputStreamReader(rbc));
        while (br.ready()) {
            System.out.println(br.readLine());
        }
        br.close();
    }
}