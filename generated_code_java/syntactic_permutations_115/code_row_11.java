import java.io.*;
public class ExecCommand {
    public static void main(String[] args) throws IOException {
        String s = "ls";
        Runtime rt = Runtime.getRuntime();
        Process p = rt.exec(s);
        InputStream in = p.getInputStream();
        BufferedReader br = new BufferedReader(new InputStreamReader(in));
        String line = null;
        while ((line = br.readLine()) != null) {
            System.out.println(line);
        }
    }
}