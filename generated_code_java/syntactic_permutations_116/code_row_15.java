import java.io.*;
public class CodeRunner{
    public static void main(String[] args) throws IOException {
        String[] cmd = {"ls", "-l"};
        Process p = Runtime.getRuntime().exec(cmd);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line = null; 
        while ((line = in.readLine()) != null) {
            System.out.println(line);
        }
    }
}