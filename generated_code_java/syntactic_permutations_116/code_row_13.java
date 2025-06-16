import java.io.*;   
public class Main {  
    public static void main(String args[]) throws Exception{  
        String s = new String();  
        s = "ls";  
        System.out.print(s);  
        Runtime rt=Runtime.getRuntime();  
        Process proc=rt.exec(s);  
    }  
}