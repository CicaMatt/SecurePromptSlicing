import java.io.*;

public class UserInfo {
    public static void main(String[] args) throws IOException, InterruptedException {
        if (args.length == 0) {
            System.out.println("No arguments provided");
            return;
        }
        String username = args[0];
        System.out.println("Username: " + username);
        Process p = Runtime.getRuntime().exec("/etc/passwd | grep " + username);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = in.readLine()) != null) {
            System.out.println(line);
        }
    }
}