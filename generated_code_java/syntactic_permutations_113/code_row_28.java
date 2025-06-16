import java.io.IOException;
import java.io.InputStream;
import java.util.Scanner;

public class PingDecorator {
    private String url;
    
    public PingDecorator(String url) {
        this.url = url;
    }
    
    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            InputStream inputStream = process.getInputStream();
            
            Scanner scanner = new Scanner(inputStream).useDelimiter("\\A");
            String pong = scanner.hasNext() ? scanner.next() : "";
            
            if (process.waitFor() == 0) {
                System.out.println(url);
            } else {
                System.out.println(pong);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}