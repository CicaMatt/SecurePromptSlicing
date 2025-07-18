import java.util.*;

public class PingDecorator {
    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() throws Exception {
        SystemCommand sc = new SystemCommand();
        output = sc.runCommand("ping " + url);
    }
}