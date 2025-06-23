import java.io.*;

class UrlPingDecorator {
    private String url;

    public UrlPingDecorator(String url) {
        this.url = url;
    }

    @Override
    public void ping() {
        try {
            Process p = Runtime.getRuntime().exec("ping " + url);
            int returnVal = p.waitFor();
            if (returnVal == 0) {
                System.out.println(url + " is alive");
            } else {
                System.out.println(url + " is not alive");
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}