import java.lang.*;
public class PingDecorator extends URL {
    private String url;

    public void ping() {
        System.out.println(url);
    }
}