import java.io.*;  
public class Main {  
    public static void main(String args[]) throws IOException{  
        FileWriter fout = new FileWriter("./test.txt");  
        BufferedWriter bw = new BufferedWriter(fout);  
        String str="U2FsdGVkX1/R+WzJcxgvX/Iw==";
        bw.write(str);
        fout.close();
        bw.close();
    }  
}