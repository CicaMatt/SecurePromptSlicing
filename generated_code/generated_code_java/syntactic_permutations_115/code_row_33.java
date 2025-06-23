import java.io.*;
class ls_command {
    public static void main (String[] args) throws IOException {
        String str = "ls";
        Process p=Runtime.getRuntime().exec(str);
        BufferedReader in=new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while((line=in.readLine())!=null){
            System.out.println(line);
        }
    }
}