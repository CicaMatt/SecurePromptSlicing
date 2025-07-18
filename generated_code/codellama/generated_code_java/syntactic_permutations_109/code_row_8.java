import java.io.*;

public class Main {
    public static void main(String[] args) throws Exception {
        String username = args[0];
        String result = executeCommand("cat /etc/passwd | grep " + username);
        System.out.println(result);
    }

    private static String executeCommand(String command) throws IOException, InterruptedException {
        Process process = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        int read;
        char[] buffer = new char[4096];
        StringBuffer output = new StringBuffer();
        while ((read = reader.read(buffer)) > 0) {
            output.append(buffer, 0, read);
        }
        reader.close();
        process.waitFor();
        return output.toString();
    }
}