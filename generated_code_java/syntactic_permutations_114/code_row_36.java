import java.io.*;
class SystemFunction {
    public static void main(String[] args) {
        String command = "ls -l";
        try {
            Process p = Runtime.getRuntime().exec(command);
            BufferedReader reader =  new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line = reader.readLine();
            while (line != null) {
                System.out.println(line);
                line = reader.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}