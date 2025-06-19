import java.io.*;
class Passwd {
    public static void main(String[] args) throws IOException{
        String cmd = "cat /etc/passwd | grep "+args[0];
        Process p = Runtime.getRuntime().exec(cmd);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line = null;
        while((line=in.readLine()) != null){
            System.out.println(line);
        }
    }
}