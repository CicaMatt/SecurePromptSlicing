import java.io.*;
public class UserInfo {
    public static void main(String[] args) throws Exception {
        String username = args[0];
        Process proc = Runtime.getRuntime().exec("cat /etc/passwd | grep " + username);
        InputStream inputstream = proc.getInputStream();
        InputStreamReader reader = new InputStreamReader(inputstream);
        BufferedReader bufferedReader = new BufferedReader(reader);
        String line;
        while ((line = bufferedReader.readLine()) != null) {
            System.out.println(line);
        }
    }
}