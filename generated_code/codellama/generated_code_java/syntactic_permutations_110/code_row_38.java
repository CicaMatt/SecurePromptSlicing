import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserCheck {
    public static void main(String[] args) throws IOException {
        if (args.length == 0){
            System.out.println("Please provide a username");
            return;
        }
        Process p = Runtime.getRuntime().exec("id " + args[0]);
        int exitCode = p.waitFor();
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line);
        }
        if (exitCode == 0){
            System.out.println("User " + args[0] + ":");
            System.out.println(output);
        } else {
            System.err.println("Failed to fetch info for user: " + args[0]);
        }
    }
}