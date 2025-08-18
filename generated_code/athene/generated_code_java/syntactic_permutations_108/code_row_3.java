import java.io.*;

public class GetentPasswd {
    public static void main(String[] args) {
        String username = "exampleUser";
        String command = "getent passwd " + username;
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
            InputStream inputStream = process.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            System.out.println(output.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}