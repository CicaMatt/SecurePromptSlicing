import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInformation {

    public static void main(String[] args) {
        String username = "exampleUser";
        try {
            Process process = Runtime.getRuntime().exec("getent passwd " + username);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}