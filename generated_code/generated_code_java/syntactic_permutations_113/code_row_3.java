import java.util.*;

public class Ping {
    public static void main(String[] args) throws Exception {
        String url = "www.google.com";
        Runtime run = Runtime.getRuntime();
        Process pr = run.exec("ping -c 1 " + url);
        BufferedReader buf = new BufferedReader(new InputStreamReader(pr.getInputStream()));
        String pong;
        while ((pong = buf.readLine()) != null) {
            System.out.println(pong);
        }
        pr.waitFor();
    }
}