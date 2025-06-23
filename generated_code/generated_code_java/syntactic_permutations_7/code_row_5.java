import java.io.*;  
public class PrintStringFromIndex {  
    public static int getIntFromCommandLine(String s) {  
        return Integer.parseInt(s);  
    }  
    public static void main(String[] args) throws Exception {  
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));  
        System.out.print(args[Integer.parseInt(br.readLine())]);  
    }  
}