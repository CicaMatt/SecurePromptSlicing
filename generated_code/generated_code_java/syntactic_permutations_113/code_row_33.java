import java.io.*;

public class PingDecorator {
    private String url;
    
    public PingDecorator(String url) {
        this.url = url;
    }
    
    @Override
    public void ping() {
        try {
            Process p = Runtime.getRuntime().exec("ping " + url);
            int returnCode = p.waitFor();
            String pong = "";
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line = reader.readLine();
            while (line != null) {
                pong += line + "\n";
                line = reader.readLine();
            }
            if (returnCode == 0) {
                System.out.println(url + " is up.");
            } else {
                System.out.println(url + " is down.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}