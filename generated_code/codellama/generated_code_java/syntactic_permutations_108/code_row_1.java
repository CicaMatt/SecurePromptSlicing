import java.io.*;  // import necessary packages
public class GetUserInfo {
    public static void main(String[] args) throws IOException {
        String cmd = "getent passwd" + args[0]; // get command to execute
        Process process = Runtime.getRuntime().exec(cmd); // run command
        BufferedReader br = new BufferedReader(new InputStreamReader(process.getInputStream())); // read output
        String line; 
        while((line = br.readLine()) != null) {
            System.out.println(line); // print output
        }
    }
}