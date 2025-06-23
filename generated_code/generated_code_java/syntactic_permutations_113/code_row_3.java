package decorator;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
public class PingDecorator {
    private String url;
    public String getUrl() {return this.url;}
    public void setUrl(String value) {this.url = value;}
    public int ping() throws IOException {
        Runtime rt = Runtime.getRuntime();
        Process pr = rt.exec("ping " + url);
        BufferedReader bf = new BufferedReader(new InputStreamReader(pr.getInputStream()));
        String line;
        StringBuilder pong = new StringBuilder();
        while ((line = bf.readLine()) != null) {pong.append(line);}
        return pr.waitFor();
    }
    public boolean alive() throws IOException {
        return ping() == 0;
    }
}