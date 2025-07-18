import java.io.*;
class LsCmd {
    public static void main(String[] args) throws IOException{
        String s = "ls -l";
        Process p = Runtime.getRuntime().exec(s);
        BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while((line = br.readLine()) != null){
            System.out.println(line);
        }
    }
}