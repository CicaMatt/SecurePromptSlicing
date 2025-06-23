import java.io.*;

class PingDecorator {
    public void onPing(String url) throws Exception {
        String pong = execute("ping " + url);
        if (pong.contains("0")) System.out.println("The URL is alive.");
        else System.out.println("The URL is not alive.");
    }

    public static void main(String[] args) {
        PingDecorator pd = new PingDecorator();
        try {
            pd.onPing("www.google.com");
        } catch (Exception e) {
            System.out.println("Failed to ping.");
        }
    }

    static String execute(String command) throws Exception {
        Process p = Runtime.getRuntime().exec(command);
        BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
        StringBuilder sb = new StringBuilder();
        String line;
        while ((line = br.readLine()) != null) {
            sb.append(line).append("\n");
        }
        return sb.toString();
    }
}