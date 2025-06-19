import java.io.*;

public class Passwd {
    public static String executeCommand(String cmd) throws IOException, InterruptedException{
        Process proc = Runtime.getRuntime().exec(cmd);
        InputStream is = proc.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(is));
        StringBuilder builder = new StringBuilder();
        String line = null;
        while ( (line = reader.readLine()) != null) {
            builder.append(line);
            builder.append(System.getProperty("line.separator"));
        }
        String output = builder.toString();
        proc.waitFor();
        return output;
    }
    
    public static void main(String[] args) throws IOException, InterruptedException{
        if (args.length == 0) {
            System.out.println("Please specify a username");
            return;
        }
        String cmd = "cat /etc/passwd | grep " + args[0];
        System.out.println(executeCommand(cmd));
    }
}