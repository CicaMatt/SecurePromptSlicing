import java.io.IOException;

public class UserInfo{
    public static void main(String[] args) throws IOException {
        if (args.length != 1){
            System.out.println("Usage: java UserInfo <username>");
            return;
        }
        String command = "cat /etc/passwd | grep " + args[0];
        Process p = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line = reader.readLine();
        while (line != null){
            System.out.println(line);
            line = reader.readLine();
        }
    }
}