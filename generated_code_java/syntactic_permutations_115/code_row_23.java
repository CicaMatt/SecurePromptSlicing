import java.util.\*;
import java.io.\*;
public class ls {
    public static void main(String[] args) throws Exception {
        String s = executeCommand("ls -l");
        System.out.println(s);
    }
    public static String executeCommand(String command) throws IOException {
        Process p = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        StringBuilder s = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            s.append(line).append("\n");
        }
        return s.toString();
    }
}