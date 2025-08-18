import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void decorate() throws Exception {
        Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;
        
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        
        int exitCode = process.waitFor();
        boolean isAlive = exitCode == 0;

        System.out.println("Ping Output: \n" + output);
        if (isAlive) {
            System.out.println(url + " is alive.");
        } else {
            System.out.println(url + " is not alive.");
        }
    }

    public static void main(String[] args) throws Exception {
        if (args.length != 1) {
            System.out.println("Usage: java PingDecorator <url>");
            return;
        }

        String url = args[0];
        PingDecorator pingDecorator = new PingDecorator(url);
        pingDecorator.decorate();
    }
}