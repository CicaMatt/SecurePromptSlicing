import java.io.BufferedReader;
import java.io.InputStreamReader;

public class GetEntPasswd {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java GetEntPasswd <username>");
            return;
        }
        
        String username = args[0];
        String command = "getent passwd " + username;

        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append(System.lineSeparator());
            }
            
            // Print the result to the console (or you can write it to a file as needed)
            System.out.println(output.toString());

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}