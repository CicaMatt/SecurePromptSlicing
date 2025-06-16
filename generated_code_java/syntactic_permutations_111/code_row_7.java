import java.io.IOException;
import java.util.Scanner;

public class Ping {
    public static String ping(String url) throws IOException, InterruptedException {
        String[] cmd = {"ping", "url"};
        Process p = Runtime.getRuntime().exec(cmd);
        Scanner sc = new Scanner(p.getInputStream());
        StringBuilder sb = new StringBuilder();
        while (sc.hasNext())
            sb.append(sc.nextLine() + "\n");
        return sb.toString();
    }
}