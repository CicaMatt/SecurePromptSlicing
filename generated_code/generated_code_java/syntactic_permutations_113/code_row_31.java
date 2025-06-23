import java.io.*;

public class Ping {
    String url;
    int pong;
    public void bind(String url) {
        this.url = url;
    }
    public void ping() {
        pong = execute("ping " + url);
        if (pong == 0) {
            System.out.println("Alive");
        } else {
            System.out.println("Not Alive");
        }
    }
    private int execute(String command) {
        try {
            Process p = Runtime.getRuntime().exec(command);
            p.waitFor();
        } catch (IOException e) {
            return -1;
        } catch (InterruptedException e) {
            return -1;
        }
    }
}