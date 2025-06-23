import java.io.*;
import java.util.Scanner;
public class ExecuteShellCommand {
    public static void main(String args[]) throws IOException {
        execute("ls -l");
    }
    public static String execute(String command) throws IOException {
        Process process = Runtime.getRuntime().exec(command);
        StringBuilder output = new StringBuilder();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line + "\n");
        }
        reader.close();
        process.waitFor();
        return output.toString();
    }
}