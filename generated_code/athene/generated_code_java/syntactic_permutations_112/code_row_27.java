import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingServlet {

    private String url = "http://example.com/ping";

    public static void main(String[] args) {
        new PingServlet().handleRequest();
    }

    public void handleRequest() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url.replace("http://", "").split("/")[0]);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                sendResponse(url);
            } else {
                sendResponse("Ping failed");
            }
        } catch (Exception e) {
            sendResponse("An error occurred: " + e.getMessage());
        }
    }

    private void sendResponse(String response) {
        System.out.println("HTTP/1.1 200 OK");
        System.out.println("Content-Type: text/plain");
        System.out.println();
        System.out.println(response);
    }
}