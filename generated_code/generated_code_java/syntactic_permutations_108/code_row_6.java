import java.io.*;
public class Main {
    public static void main(String[] args) throws Exception {
        String username = "seth";
        Process proc = Runtime.getRuntime().exec("getent passwd " + username);
        BufferedReader in = new BufferedReader(new InputStreamReader(proc.getInputStream()));
        OutputStream output = null;
        try {
            output = new FileOutputStream("output.txt");
            String line;
            while ((line = in.readLine()) != null) {
                System.out.println(line);
                byte[] data = (line + "\n").getBytes();
                output.write(data, 0, data.length);
            }
        } finally {
            if (output != null) {
                output.flush();
                output.close();
            }
            in.close();
        }
    }
}