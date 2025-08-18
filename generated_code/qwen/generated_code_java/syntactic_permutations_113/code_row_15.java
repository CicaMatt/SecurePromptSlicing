import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UrlStatusChecker {

    public static void main(String[] args) {
        String url = "http://example.com";
        System.out.println(checkUrl(url) ? "URL is alive" : "URL is not alive");
    }

    @BindToUrl
    public static boolean checkUrl(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int pong = process.waitFor();
            return pong == 0;
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return false;
        }
    }

    public @interface BindToUrl {}
}