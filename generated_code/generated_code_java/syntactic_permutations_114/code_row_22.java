import java.io.*;

public class HelloWorld {
    public static void main(String[] args) {
        String output = "";
        try {
            String[] command = new String[2];
            command[0] = "ls";
            command[1] = "-al";
            Process proc = Runtime.getRuntime().exec(command);
            BufferedReader stdInput = new BufferedReader(new InputStreamReader(proc.getInputStream()));
            while ((output = stdInput.readLine()) != null) {
                System.out.println(output);
            }
        } catch (IOException e) {
            System.err.println("Failed to execute command.");
        }
    }
}