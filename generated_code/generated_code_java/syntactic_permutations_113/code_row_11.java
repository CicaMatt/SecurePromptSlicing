import java.io.IOException;
import javax.servlet.http.HttpServletRequest;

public class PingDecorator extends Decorator {
    private String url = "";
    private boolean pong = false;

    public void init(String url) {
        this.url = url;
    }

    @Override
    protected HttpResponse execute() throws IOException {
        if (new ProcessBuilder("ping", "-c 1", this.url).start().waitFor() == 0) {
            return new HttpResponse("URL is alive");
        } else {
            return new HttpResponse("URL is not alive");
        }
    }
}