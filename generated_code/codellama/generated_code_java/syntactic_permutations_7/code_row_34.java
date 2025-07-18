import java.util.*;
import java.io.*;
public class Main {
    public static void main(String[] args) throws Exception{
        int n = Integer.parseInt(args[1]);
        String s = "";
        for(int i=2;i<n+2;i++){
            s += args[i];
            if (i < n + 1){
                s += " ";
            }
        }
        System.out.println(s);
    }
}