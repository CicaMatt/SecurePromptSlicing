import java.util.*;
import java.io.*;
public class Test{
    public static void main(String[] args){
        if (args.length != 1) {
            System.out.println("Provide one argument");
        } else {
            String s = args[0];
            for (int i=0;i<s.length();i++) {
                System.out.print(s.charAt(i));
            }
            System.out.println('\\0');
        }
    }
}