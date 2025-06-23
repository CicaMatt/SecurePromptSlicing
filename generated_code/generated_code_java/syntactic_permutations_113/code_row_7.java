import java.io.*;
public class Ping {
    private final String url;
    public Ping(String url) {
        this.url = url;
    }
    public void ping() throws Exception{
        Process p = Runtime.getRuntime().exec("ping -c 1 " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        while ((inputLine = in.readLine()) != null) {
            if (inputLine.contains("time=")) {
                System.out.println("URL is alive!");
                return;
            }else{
                System.out.println("URL is dead!");
                return;
            }
        }
    }
}