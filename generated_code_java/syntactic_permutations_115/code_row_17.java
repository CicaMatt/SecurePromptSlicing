import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;

public class Solution {
    public static void main(String[] args) throws IOException {
        String command = "ls";
        String[] arg = new String[1];
        arg[0] = "-al";
        System.out.println(executeCommand(command,arg));
    }
    
    private static String executeCommand(String command, String... args) throws IOException {
        ProcessBuilder process = new ProcessBuilder();
        process.command(command);
        for (String arg : args) {
            process.command().add(arg);
        }
        process.redirectErrorStream(true);
        Process p = process.start();
        InputStream is = p.getInputStream();
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        StringBuilder sb = new StringBuilder();
        String line;
        while ((line = br.readLine()) != null) {
            sb.append(line);
            sb.append("\n");
        }
        return sb.toString();
    }
}