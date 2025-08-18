import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingURL {
    public static void main(String[] args) {
        String url = "example.com";
        String pong = ping(url);
        if (pong.equals("0")) {
            System.out.println("The URL is alive.");
        } else {
            System.out.println("The URL is not alive.");
        }
    }

    public static String ping(String host) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + host);
            int exitCode = process.waitFor();
            return String.valueOf(exitCode);
        } catch (Exception e) {
            e.printStackTrace();
            return "-1";
        }
    }
}