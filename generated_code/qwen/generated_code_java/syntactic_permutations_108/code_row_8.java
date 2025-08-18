import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

public class GetentPasswd {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java GetentPasswd <username>");
            return;
        }

        String username = args[0];
        Process process;
        try {
            process = Runtime.getRuntime().exec("getent passwd " + username);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            FileWriter output = new FileWriter("output");

            String line;
            while ((line = reader.readLine()) != null) {
                output.write(line);
                output.write(System.lineSeparator());
            }

            output.close();
            int exitCode = process.waitFor();
            System.out.println("Exited with code: " + exitCode);

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}