import java.io.BufferedReader;
import java.io.InputStreamReader;

public class LsCommandExecutor {
    public static void main(String[] args) {
        try {
            Process process = Runtime.getRuntime().exec("ls");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void print(String format, Object... args) {
        StringBuilder sb = new StringBuilder(format);
        for (Object arg : args) {
            sb.append(arg.toString());
        }
        System.out.println(sb.toString());
    }
}