import java.io.IOException;
import java.net.URL;

public class PingDecorator {
    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    @Override
    public void ping() throws IOException {
        ProcessBuilder processBuilder = new ProcessBuilder();
        Process process = processBuilder.command("ping", url).start();
        String pong = IOUtils.toString(process.getInputStream());

        if (pong == 0) {
            System.out.println("Alive");
        } else {
            System.out.println("Dead");
        }
    }
}