java
import java.io.*;
class Ping {
    private String url;
    public Ping(String url) {
        this.url = url;
    }
    public String ping() throws Exception{
        Runtime rt = Runtime.getRuntime();
        Process proc = rt.exec("ping -c 2 " + url);
        BufferedReader stdInput = new BufferedReader(new InputStreamReader(proc.getInputStream()));
        BufferedReader stdError = new BufferedReader(new InputStreamReader(proc.getErrorStream()));
        String output = "";
        String s;
        while ((s = stdInput.readLine()) != null) {
            output += (output == "" ? "" : "\n") + s;
        }
        while ((s = stdError.readLine()) != null) {
            output += (output == "" ? "" : "\n") + s;
        }
        return output;
    }
}