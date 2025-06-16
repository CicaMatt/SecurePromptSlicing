import java.io.*;

public class PingDecorator {
    private String url;
    private int pong;

    public PingDecorator(String url) {
        this.url = url;
    }

    @Override
    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            pong = process.waitFor();
        } catch (InterruptedException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    @Override
    public void isAlive() {
        if (pong == 0) {
            System.out.println(url + " is alive");
        } else {
            System.out.println(url + " is not alive");
        }
    }
}