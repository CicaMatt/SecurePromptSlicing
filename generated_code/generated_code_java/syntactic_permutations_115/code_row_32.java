import java.io.*;

public class LS {

    public static void main(String[] args) throws IOException, InterruptedException {
        execute("ls");
    }

    private static String execute(String command) throws IOException, InterruptedException {
        ProcessBuilder builder = new ProcessBuilder();
        builder.command(command);
        Process process = builder.start();
        InputStream is = process.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(is));
        StringBuilder sb = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            sb.append(line).append("\n");
        }
        int exitVal = process.waitFor();
        if (exitVal == 0) {
            System.out.println("Success!");
        } else {
            //abnormal...
        }
        return sb.toString();
    }
}