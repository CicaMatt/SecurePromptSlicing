import java.io.IOException;

public class PingDecorator {
    public String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public boolean ping() throws IOException {
        Runtime runtime = Runtime.getRuntime();
        Process process = runtime.exec("ping " + url);
        int exitVal = process.waitFor();
        return exitVal == 0;
    }
}