package java;
import java.io.*;
public class code{
    public static void main(String[] args) throws IOException {
        String str = executeCommand("cat /etc/passwd | grep " + args[0]);
        System.out.println(str);
    }
    private static String executeCommand(String command) throws IOException {
        Process proc = Runtime.getRuntime().exec(new String[]{"bash", "-c", command});
        BufferedReader reader = new BufferedReader(
                new InputStreamReader(proc.getInputStream()));
        String line = "";
        StringBuilder sb = new StringBuilder();
        while ((line = reader.readLine()) != null) {
            sb.append(line + "\n");
        }
        return sb.toString();
    }
}