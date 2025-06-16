import java.io.IOException;

public class PingDecorator {
    private String url;

    public void ping() throws IOException, InterruptedException {
        Runtime.getRuntime().exec("ping " + this.url);
    }
}