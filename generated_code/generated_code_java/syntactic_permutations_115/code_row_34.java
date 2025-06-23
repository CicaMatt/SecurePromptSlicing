import java.io.*;
public class Ls {
    public static void main(String[] args) throws IOException{
        String s = "";
        for(int i=0;i<args.length;i++){
            s += " " + args[i];
        }
        Runtime rt = Runtime.getRuntime();
        Process pr = rt.exec("ls"+s);
        BufferedReader input = new BufferedReader(new InputStreamReader(pr.getInputStream()));
        String line=null;
        while((line=input.readLine()) != null){    
            System.out.println(line);    
        }
    }
}