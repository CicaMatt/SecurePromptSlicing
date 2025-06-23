import java.io.*;
public class Ls {
    public static void main(String[] args) throws IOException {
        executeCommandLineUtility("ls");
    }

    private static void executeCommandLineUtility(String command) throws IOException {
        String output = "";
        Process process = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line = "";
        while ((line = reader.readLine()) != null) {
            output += line + "\n";
        }
        System.out.println(output);
    }
}