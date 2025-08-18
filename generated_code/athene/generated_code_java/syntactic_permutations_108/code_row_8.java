import java.io.BufferedReader;
import java.io.InputStreamReader;

public class GetUserInformation {
    public static void main(String[] args) {
        String username = args[0];
        String command = "getent passwd " + username;
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}