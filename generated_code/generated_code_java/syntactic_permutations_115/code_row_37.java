import java.io.*;
public class Test{
    public static void main(String[] args) throws IOException {
        String s = "ls -l";
        executeCmd(s);
    }
    private static void executeCmd(String command) throws IOException {
        Process p = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }
}