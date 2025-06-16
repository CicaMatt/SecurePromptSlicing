import java.io.IOException;
import org.apache.commons.io.IOUtils;

public class Ping {
    public String ping(String url) throws IOException {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", url);
        Process process = processBuilder.start();
        return IOUtils.toString(process.getInputStream());
    }
}