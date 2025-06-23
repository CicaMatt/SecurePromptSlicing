import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        String command = "ls";
        executeCommand(command);
    }
    public static void executeCommand(String command) throws IOException {
        Runtime rt = Runtime.getRuntime();
        Process proc = rt.exec(command);

        BufferedReader stdInput = new BufferedReader(new InputStreamReader(proc.getInputStream()));

        // read the output from the command
        String s = null;
        while ((s = stdInput.readLine()) != null) {
            System.out.println(s);
        }
    }
}