import java.io.BufferedReader;
import java.io.InputStreamReader;

public class GetentCommandExecutor {
    public static void main(String[] args) {
        String username = "exampleUser";
        String command = "getent passwd " + username;
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            System.out.print(output.toString());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}