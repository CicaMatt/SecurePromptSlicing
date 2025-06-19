import java.io.*;
public class ExecutingLs {
    public static void main(String[] args) throws IOException {
        String output= "";
        Process p = Runtime.getRuntime().exec("ls");
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line = reader.readLine();
        while (line != null) {
            output += line + "\n";
            line = reader.readLine();
        }
        System.out.println("The current directory contains the following files:\n" + output);
    }
}