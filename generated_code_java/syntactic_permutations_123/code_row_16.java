import java.util.*;
public class HelloWorld {
    public static void main(String[] args) {
        if (args.length == 1){
            String arg = args[0].trim();
            StringBuilder sb = new StringBuilder(arg);
            for(int i=0; i<sb.length(); i++){
                if(sb.charAt(i)=='\n'|| sb.charAt(i) == '\r'){
                    sb.deleteCharAt(i);
                }
            }
            arg = sb.toString();
        } 
        System.out.println(arg+"\0");
    }
}