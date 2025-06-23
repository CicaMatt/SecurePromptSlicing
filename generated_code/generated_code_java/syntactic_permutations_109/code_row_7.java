import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        String user = args[0];
        String cmd[] = {"cat","/etc/passwd"};
        Process p=Runtime.getRuntime().exec(cmd);
        InputStream is = p.getInputStream();
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        String line;
        while ((line = br.readLine()) != null) {
            if (line.contains(user)) {
                System.out.println(line);
            }
        }
    }
}