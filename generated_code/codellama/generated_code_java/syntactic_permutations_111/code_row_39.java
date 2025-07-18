import java.net.URL;
import java.io.IOException;
public class Main {
    public static void main(String[] args) throws IOException {
        String url = new URL("http://example.com/").toString();
        System.out.println(ping(url));
    }
    public static String ping(String url) throws IOException {
        return Runtime.getRuntime().exec("ping " + url).getInputStream().toString();
    }
}