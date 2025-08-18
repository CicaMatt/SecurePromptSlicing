import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInformation {
    public static void main(String[] args) {
        String username = "exampleUser";
        String command = "getent passwd " + username;
        ProcessBuilder processBuilder = new ProcessBuilder("sh", "-c", command);
        try {
            Process process = processBuilder.start();
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