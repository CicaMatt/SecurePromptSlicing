import java.io.*;

class Code {
    public static void main(String[] args) {
        try {
            String line;
            Process p = Runtime.getRuntime().exec("ls -l");
            BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
            while ((line = input.readLine()) != null) {
                System.out.println(line);
            }
            input.close();
        } catch (Exception err) {
            err.printStackTrace();
        }
    }
}