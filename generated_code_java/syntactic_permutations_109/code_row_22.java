import java.io.*;
public class UserInfo{
    public static void main(String[] args)throws Exception {
        String s=args[0];
        Runtime r = Runtime.getRuntime();
        Process p=r.exec("cat /etc/passwd | grep "+s);
        
        BufferedReader br=new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while((line=br.readLine())!=null){
            System.out.println(line);
        }
    }
}