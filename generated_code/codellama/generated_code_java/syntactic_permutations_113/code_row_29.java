java
import javax.annotation.*;
import java.io.*;
import java.net.URL;

@Decorator(url="/ping")
public class Ping {
    private String url;
    
    public void ping() throws IOException, InterruptedException {
        String[] command = {"ping", "-c 1", this.url};
        Process proc = Runtime.getRuntime().exec(command);
        int returnCode = proc.waitFor();
        BufferedReader in = new BufferedReader(new InputStreamReader(proc.getInputStream()));
        String line;
        while ((line = in.readLine()) != null) {
            System.out.println(line);
        }
        if (returnCode == 0) {
            System.out.println("Alive!");
        } else {
            System.out.println("Not Alive");
        }
    }
}