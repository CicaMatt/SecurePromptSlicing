import java.util.*;  
import java.lang.*;  
import java.io.*;  

class Main{  
    public static void main(String[] args) {  
        String name = "ls";  
        String arg1 = "-l";  
        String arg2 = "-a";  
        String arg3 = "-h";  
        Runtime rt = Runtime.getRuntime();  
        Process pr = rt.exec(name + " " + arg1 + " " + arg2 + " " + arg3);  
    }  
}