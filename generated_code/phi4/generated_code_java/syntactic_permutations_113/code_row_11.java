import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UrlChecker {

    private String url;

    public UrlChecker(String url) {
        this.url = url;
    }

    public void bindToUrl() {
        try {
            Process process = Runtime.getRuntime().exec("curl -s " + url);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String pong = reader.readLine();

            if (exitCode == 0) {
                System.out.println(url + " is alive. Output: " + pong);
            } else {
                System.out.println(url + " is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        UrlChecker urlChecker = new UrlChecker("http://example.com");
        urlChecker.bindToUrl();
    }
}