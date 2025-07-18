import java.io.InputStreamReader;

public class PingDecorator {
    public static void ping(String url) throws Exception {
        String[] commands = new String[] {"ping", url};
        Process process = Runtime.getRuntime().exec(commands);
        InputStreamReader reader = new InputStreamReader(process.getInputStream());
        int c;
        StringBuilder sb = new StringBuilder();
        while ((c = reader.read()) != -1) {
            sb.append((char) c);
        }
        String output = sb.toString();
        System.out.println(output);
    }
}