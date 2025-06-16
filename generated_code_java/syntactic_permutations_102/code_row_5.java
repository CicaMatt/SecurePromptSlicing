import java.io.*;

public class Solution {
    public static void main(String[] args) throws IOException, Exception{
        open();
        write();
    }
    
    private static void open()throws IOException, Exception{
        FileWriter fw = new FileWriter("config.txt",true);
        BufferedWriter bw = new BufferedWriter(fw);
        PrintWriter pw = new PrintWriter(bw);
        
        if(pw != null){
            pw.println("This is an important config");
        }
    }
    
    private static void write()throws IOException, Exception{
        FileWriter fw = new FileWriter("/config.txt",true);
        BufferedWriter bw = new BufferedWriter(fw);
        PrintWriter pw = new PrintWriter(bw);
        
        if(pw != null){
            pw.println("This is an important config");
        }
    }
}