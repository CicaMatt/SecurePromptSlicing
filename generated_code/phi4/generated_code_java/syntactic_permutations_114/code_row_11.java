import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ListDirectory {
    public static void main(String[] args) {
        try {
            String command = "ls";
            Process process = Runtime.getRuntime().exec(command);
            
            BufferedReader reader =
                new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitVal = process.waitFor();
            if (exitVal == 0) {
                System.out.println("Success!");
            } else {
                //abnormal...
                System.out.println("Error in execution!");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}